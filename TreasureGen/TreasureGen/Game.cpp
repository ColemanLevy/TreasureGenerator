//-----------------------------------------------
//Name: Coleman Levy
//Date: 8/16/19
//Description: A game with a focus on random treasure generator,
//			   a store where you can purchase equipment, and the player
//			   having equipment to equip and choose from
//-----------------------------------------------

//The using statements in the game for the created header files
#include "Headers/GHeader.h"
#include "Headers/Texture.h"
#include "Headers/Components.h"
#include "Headers/Vector2D.h"
#include "Headers/Hero.h"
#include "Headers/Enemy.h"
#include "Headers/Treasure.h"

//The renderer and event handler used in the game
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

//The manager that the game uses to manage the entities in the game
Manager manager;

//The player character with its stats and equipment
Character* player = new Character();
//The enemy used in the game
Enemy* enemy = new Enemy();
//The treasure used in the game
Treasure* treasure = new Treasure();

//The string used for loading from the save file
string loading;

//Integer used for random values
int random;
//Integer used to show how many turns the player has left to attack
int currentSpeed;
//Integer that indicates which page of the pause menu the player is on
int pageNum;
//Integer that stores how much gold the player has
int gold = 100;
//Integers used for the health bar to show max health for both player and enemy
int enemyH;
int playerH;

//Boolean that indicates if the player is fighting in the colosseum
bool fightMode = false;
//Boolean that indicates if the player is in the store
bool storeMode = false;
//Boolean that indicates if the player won the current fight
bool battleWin = false;
//Boolean that indicates if this is the player's first fight in the colosseum
bool firstFight = true;

//Color variable used for parsing into the text components message creation
//Initialized to be black
SDL_Color color = { 0, 0, 0 };

//The in and out stream variables used for saving and loading
ifstream inFile;
ofstream outFile;

//The objects shown on screen for the game
auto& field(manager.addEntity());
auto& colosseum(manager.addEntity());
auto& slime(manager.addEntity());
auto& store(manager.addEntity()); 
auto& church(manager.addEntity()); 

//The text shown on screen for the game
auto& statsText(manager.addEntity());
auto& goldText(manager.addEntity()); 
auto& extraText(manager.addEntity()); 

//All of the buttons used in the game
auto& storeButton1(manager.addEntity()); 
auto& storeButton2(manager.addEntity()); 
auto& storeButton3(manager.addEntity()); 
auto& storeButton4(manager.addEntity()); 
auto& storeButton5(manager.addEntity()); 
auto& storeButton6(manager.addEntity()); 
auto& pauseButton(manager.addEntity()); 
auto& resumeButton(manager.addEntity()); 
auto& yesButton(manager.addEntity()); 
auto& noButton(manager.addEntity()); 
auto& saveButton(manager.addEntity());
auto& resetButton(manager.addEntity()); 
auto& nextButton(manager.addEntity()); 
auto& prevButton(manager.addEntity()); 
auto& exitButton(manager.addEntity()); 

//Function for loading the character's saved equipment set and gold amount
void load()
{
	//Opens the save file
	inFile.open("Save.txt");
	inFile >> loading;
	//If the file isn't empty, proceed to load in the equipment set
	if (loading != "")
	{
		//Close and reopen save file to start back at the beginning
		inFile.close();
		inFile.open("Save.txt");
		//For each of the equipment in the save file..
		for (int i = 0; i < 6; i++)
		{
			//Resets the equipment name
			player->equipment[i]->name = "";
			inFile >> loading;
			//Loads in the equipment name
			player->equipment[i]->name += loading;
			inFile >> loading;
			//While the string being read from the save file isn't a period,
			//continue adding words to the equipment name from the save file
			while (loading != ".")
			{
				player->equipment[i]->name += " ";
				player->equipment[i]->name += loading;
				inFile >> loading;
			}
			//Then load in the stats and and the element of the saved equipment
			inFile >> player->equipment[i]->atk;
			inFile >> player->equipment[i]->def;
			inFile >> player->equipment[i]->element->type;
		}
		//Once all of the equipment is loaded in, load the saved gold amount
		inFile >> gold;
	}
	//Close the save file
	inFile.close();
}

//Function for saving the character's current equipment set and gold amound
void save()
{
	//Open the save file
	outFile.open("Save.txt");
	//For each of the equipment the character has...
	for (int i = 0; i < 6; i++)
	{
		//Save the equipment's name, and add a period to the end to indicate the end
		//of the equipment name for the loader
		outFile << player->equipment[i]->name << " ." << endl;
		//Save the stats and element of the equipment
		outFile << player->equipment[i]->atk << endl;
		outFile << player->equipment[i]->def << endl;
		outFile << player->equipment[i]->element->type << endl;
	}
	//Save the gold amount
	outFile << gold;
	//Close the save file
	outFile.close();
}

//A short function to speed up object creation
void creObject(Entity* entity, int x, int y, int w, int h, string texture)
{
	//For the parsed object, add in its transform component
	entity->addComponent<TransformComponent>(x, y);
	entity->getComponent<TransformComponent>().height = h;
	entity->getComponent<TransformComponent>().width = w;
	//If there is a parsed texture, add said texture to the entity
	if (texture != "")
	{
		entity->addComponent<SpriteComponent>(&texture[0]);
	}
}

//A short function to speed up button creation
void creButton(Entity* entity, int w, int h)
{
	//Add the button component with the parsed size to the entity
	entity->addComponent<ButtonComponent>();
	entity->getComponent<ButtonComponent>().height = h;
	entity->getComponent<ButtonComponent>().width = w;
}

//A short function to speed up text creation
void creText(Entity* entity, string text, int line, SDL_Color color)
{
	//Add the text component to the parsed entity, and if the message parsed
	//isn't empty, then add said message to the text component
	if (text != "")
	{
		entity->addComponent<TextComponent>(&text[0], line, color);
	}
	//Otherwise, just add the text component without any message
	else
	{
		entity->addComponent<TextComponent>();
	}
}

//Function that initializes all of the components for all of the objects
void initializer()
{
	//Objects-----------------------------------------------------------------
	//Creates the components for all of the objects in the game (objects being
	//the enemy, background, and all of the locations on the screen)

	creObject(&colosseum, 100, 200, 192, 192, "Assets/Colosseum.png");
	creButton(&colosseum, 192, 152);

	creObject(&store, 550, 400, 250, 250, "Assets/Store(TG).png");
	creButton(&store, 225, 152);
	
	creObject(&church, 200, 400, 300, 300, "Assets/Church(TG).png");
	creButton(&church, 225, 200);

	creObject(&field, 0, 0, 832, 640, "Assets/Field(TG).png");

	creObject(&slime, -1000, -1000, 128, 128, "Assets/Slime1(TG).png");
	creButton(&slime, 128, 128);

	//Buttons---------------------------------------------------------------------------
	//Creates the components for all of the buttons in the game

	creObject(&pauseButton, 0, 0, 128, 64, "Assets/PauseButt(TG).png");
	creButton(&pauseButton, 128, 64);

	creObject(&storeButton1, -1000, -1000, 300, 75, "Assets/storeButton(TG).png");
	creButton(&storeButton1, 300, 75);
	creText(&storeButton1, "Random Helmet Cost: 100", 100, color);

	creObject(&storeButton2, -1000, -1000, 300, 75, "Assets/storeButton(TG).png");
	creButton(&storeButton2, 300, 75);
	creText(&storeButton2, "Random Chestplt Cost: 100", 100, color);
	
	creObject(&storeButton3, -1000, -1000, 300, 75, "Assets/storeButton(TG).png");
	creButton(&storeButton3, 300, 75);
	creText(&storeButton3, "Random Gloves Cost: 100", 100, color);
	
	creObject(&storeButton4, -1000, -1000, 300, 75, "Assets/storeButton(TG).png");
	creButton(&storeButton4, 300, 75);
	creText(&storeButton4, "Random Boots Cost: 100", 100, color);
	
	creObject(&storeButton5, -1000, -1000, 300, 75, "Assets/storeButton(TG).png");
	creButton(&storeButton5, 300, 75);
	creText(&storeButton5, "Random Rune Cost: 100", 100, color);
	
	creObject(&storeButton6, -1000, -1000, 300, 75, "Assets/storeButton(TG).png");
	creButton(&storeButton6, 300, 75);
	creText(&storeButton6, "Random Weapon Cost: 100", 100, color);

	creObject(&exitButton, -1000, -1000, 128, 100, "Assets/ExitArr.png");
	creButton(&exitButton, 128, 100);
	color = { 0, 200, 0 };
	creText(&exitButton, "Exit", 100, color);
	color = { 0, 0, 0 };

	creObject(&resumeButton, -1000, -1000, 128, 64, "Assets/ResumeButt(PG).png");
	creButton(&resumeButton, 128, 64);

	creObject(&yesButton, -1000, -1000, 128, 64, "Assets/YesButt(TG).png");
	creButton(&yesButton, 128, 64);

	creObject(&noButton, -1000, -1000, 128, 64, "Assets/NoButt(TG).png");
	creButton(&noButton, 128, 64);
	
	creObject(&saveButton, -1000, -1000, 128, 64, "Assets/SaveButt(TG).png");
	creButton(&saveButton, 128, 64);

	creObject(&resetButton, -1000, -1000, 128, 64, "Assets/ResetButt(PG).png");
	creButton(&resetButton, 128, 64);

	creObject(&nextButton, -1000, -1000, 64, 64, "Assets/NextArr.png");
	creButton(&nextButton, 64, 64);

	creObject(&prevButton, -1000, -1000, 64, 64, "Assets/PrevArr.png");
	creButton(&prevButton, 64, 64);

	//Texts------------------------------------------------------------------------------
	//Creates the components for all of the text objects in the game

	creObject(&statsText, -1000, -1000, 400, 100, "Assets/storeButton(TG).png");
	creText(&statsText, "", 0, color);

	creObject(&goldText, -1000, -1000, 250, 75, "");
	creText(&goldText, "", 0, color);

	creObject(&extraText, -1000, -1000, 400, 100, "Assets/storeButton(TG).png");
	creText(&extraText, "", 0, color);
}

//Small function for changing the position of the parsed entity
void setPos(Entity* entity, int x, int y)
{
	//Set the x position
	entity->getComponent<TransformComponent>().position.x = x;
	//Set the y position
	entity->getComponent<TransformComponent>().position.y = y;
}

//Small function for changing the size of the parsed entity
void setSize(Entity* entity, int w, int h)
{
	//Set the width
	entity->getComponent<TransformComponent>().width = w;
	//Set the height
	entity->getComponent<TransformComponent>().height = h;
}

//Small function for setting the message of the text of an entity
void setText(Entity* entity, string text, int line, SDL_Color color)
{
	//Set the text
	entity->getComponent<TextComponent>().setTex(&text[0], line, color);
}

//Small function that sets the text for goldText. Put in a separate function
//because of needing to repeatedly set color to white
void updGoldT()
{
	//Set color back to white
	color = { 255, 255, 255 };
	//Actually sets message
	setText(&goldText, "Gold: " + to_string(gold), 100, color);
	//Resets color to black
	color = { 0, 0, 0 };
}

//Small function that sets the text for statsText. Put in a separate function
//because of needing to repeatedly set color to white. Also allows for changing the
//size of the statsText entity
void updStatT(string text, int line, int w, int h)
{
	//Set color back to white
	color = { 255, 255, 255 };
	//Actually sets message
	setText(&statsText, text, line, color);
	//Resets color to black
	color = { 0, 0, 0 };
	//Changes the size of the statsText to be what was parsed
	setSize(&statsText, w, h);
}

//Small function that sets the text for extraText. Put in a separate function
//because of needing to repeatedly set color to white. Also allows for changing the
//size of the extraText entity
void updExtraT(string text, int line, int w, int h)
{
	//Set color back to white
	color = { 255, 255, 255 };
	//Actually sets message
	setText(&extraText, text, line, color);
	//Resets color to black
	color = { 0, 0, 0 };
	//Changes the size of the extraText to be what was parsed
	setSize(&extraText, w, h);
}

//Function that sets multiple objects to preset positions. Used
//for quick repeated mass object movement
void moveObjects(int quad)
{
	//Makes the movements based on which type of movement was requested
	switch (quad)
	{
		//Movement for getting locations off screen
	case 0:
		setPos(&colosseum, -1000, -1000);
		setPos(&store, -1000, -1000);
		setPos(&church, -1000, -1000);
		break;
		//Movement for getting rid of any menus
	case 1:
		setPos(&colosseum, 100, 200);
		setPos(&store, 550, 400);
		setPos(&church, 200, 400);
		setPos(&pauseButton, 0, 0);
		setPos(&yesButton, -1000, -1000);
		setPos(&noButton, -1000, -1000);
		setPos(&resetButton, -1000, -1000);
		setPos(&saveButton, -1000, -1000);
		setPos(&nextButton, -1000, -1000);
		setPos(&prevButton, -1000, -1000);
		setPos(&statsText, -1000, -1000);
		setPos(&extraText, -1000, -1000);
		setPos(&resumeButton, -1000, -1000);
		break;
		//Movement for bring store buttons onto screen
	case 2:
		setPos(&storeButton1, 250, 10);
		setPos(&storeButton2, 250, 110);
		setPos(&storeButton3, 250, 210);
		setPos(&storeButton4, 250, 310);
		setPos(&storeButton5, 250, 410);
		setPos(&storeButton6, 250, 510);
		setPos(&exitButton, 50, 530);
		setPos(&goldText, 550, 200);
		break;
		//Movement for moving store buttons off of the screen
	case 3:
		setPos(&storeButton1, -1000, -1000);
		setPos(&storeButton2, -1000, -1000);
		setPos(&storeButton3, -1000, -1000);
		setPos(&storeButton4, -1000, -1000);
		setPos(&storeButton5, -1000, -1000);
		setPos(&storeButton6, -1000, -1000);
		setPos(&exitButton, -1000, -1000);
		setPos(&goldText, -1000, -1000);
		break;
		//Movement for moving save menu and treasure menu off screen
	case 4:
		setPos(&yesButton, -1000, -1000);
		setPos(&noButton, -1000, -1000);
		setPos(&statsText, -1000, -1000);
		setPos(&extraText, -1000, -1000);
		setPos(&resumeButton, -1000, -1000);
		break;
		//Movement for bringing treasure menu onto screen
	case 5:
		setPos(&yesButton, 250, 550);
		setPos(&noButton, 450, 550);
		setPos(&statsText, 200, 100);
		setPos(&extraText, 200, 300);
		break;
		//Movement for bring save menu onto screen
	case 6:
		setPos(&colosseum, -1000, -1000);
		setPos(&store, -1000, -1000);
		setPos(&church, -1000, -1000);
		setPos(&pauseButton, -1000, -1000);
		setPos(&saveButton, 250, 400);
		setPos(&resetButton, 450, 400);
		setPos(&resumeButton, 350, 500);
		setPos(&statsText, 200, 100);
		break;
		//Movement for brining pause menu onto screen
	case 7:
		setPos(&statsText, 200, 50);
		setPos(&resumeButton, 350, 550);
		setPos(&nextButton, 750, 300);
		setPos(&prevButton, 10, 300);
		setPos(&pauseButton, -1000, -1000);
		setPos(&slime, -1000, -1000);
		break;
		//Movement for the save menu second form
	case 8:
		setPos(&resumeButton, -1000, -1000);
		setPos(&resetButton, -1000, -1000);
		setPos(&saveButton, -1000, -1000);
		setPos(&yesButton, 250, 400);
		setPos(&noButton, 450, 400);
		break;
		//Movement to make health bars
	case 9:
		setPos(&statsText, 600, 10);
		setPos(&extraText, 10, 590);
		break;
		//Movement to remove health bars
	case 10:
		setPos(&statsText, -1000, -1000);
		setPos(&extraText, -1000, -1000);
		//If input type unknown, don't do any movement
	default:
		break;
	}
}

//Small function to pass the found treasure into the appropriate player's equipment slot
void equipEdit(int num, string name, int atk, int def, int elem)
{
	//Set the name, atk, def, and element of the equipment to be the treasure's name, atk, def, and element
	player->equipment[num]->name = name;
	player->equipment[num]->atk = atk;
	player->equipment[num]->def = def;
	player->equipment[num]->element->type = elem;
}

//A function for waiting on the player to click the yes or no buttons
void Game::itemLoop()
{
	//Wait for the player to click the yes or no buttons, while still keeping the updating, rendering, and events working
	//so that the player is able to click the buttons
	while (!yesButton.getComponent<ButtonComponent>().press && !noButton.getComponent<ButtonComponent>().press)
	{
		SDL_PollEvent(&event);
		manager.refresh();
		manager.update();
		render();
	}
	//Just ends once one of the buttons is clicked
}

//Function for randomly generating treasure
void Game::generateTreas(int type)
{
	//The highest chance is for the player to get between 1 and 100 gold
	if (type <= 5)
	{
		//Adds gold found to gold amount
		gold += treasure->gold();
		//Writes out how much gold has been found
		updStatT("You have found " + to_string(treasure->amount) + " gold!", 200, 400, 100);
		//Writes out the new gold amount
		updGoldT();
		//Brings the text and yes button onto screen
		setPos(&statsText, 200, 100);
		setPos(&yesButton, 350, 550);
		//Waits until the yes button is pressed
		itemLoop();
		//If in the store, returns store buttons
		if (storeMode)
		{
			moveObjects(2);
		}
		//Removes the treasure menu
		moveObjects(4);
		//Sets yes button to false to prevent repeated yes presses
		yesButton.getComponent<ButtonComponent>().press = false;
	}
	//Player has chance to find weapon
	else if (type <= 7)
	{
		//Generates a random weapon
		treasure->weapon();
		//Writes out the weapon found
		updStatT("You have found a weapon! Name: " + treasure->name + " | Attack power: " + to_string(treasure->atk) + " | Equip it?",
			200, 400, 200);
		//Writes out the weapon the player currently has
		updExtraT("Your current weapon: " + player->equipment[5]->name + " | Attack power: " + to_string(player->equipment[5]->atk),
			200, 400, 200);
		//Moves the treasure menu onto screen
		moveObjects(5);
		//Wait for the yes or no key to be pressed
		itemLoop();
		//If the yes button is pressed, replace current weapon with found weapon
		if (yesButton.getComponent<ButtonComponent>().press)
		{
			equipEdit(5, treasure->name, treasure->atk, treasure->def, treasure->element);
		}
		//If in the store, returns store buttons
		if (storeMode)
		{
			moveObjects(2);
		}
		//Removes the treasure menu
		moveObjects(4);
		//Sets yes and no buttons to false to prevent repeated yes and no presses
		noButton.getComponent<ButtonComponent>().press = false;
		yesButton.getComponent<ButtonComponent>().press = false;
	//Player has chance to find helmets
	}
	else if (type <= 9)
	{
		//Generates a random helmet
		treasure->helmet();
		//Writes out the helmet found
		updStatT("You have found a helmet! Name: " + treasure->name + " | Defense power: " + to_string(treasure->def) + " | Equip it?", 
			200, 400, 200);
		//Writes out the helmet the player currently has
		updExtraT("Your current helmet: " + player->equipment[0]->name + " | Defense power: " + to_string(player->equipment[0]->def),
			200, 400, 200);
		//Moves the treasure menu onto screen
		moveObjects(5);
		//Wait for the yes or no key to be pressed
		itemLoop();
		//If the yes button is pressed, replace current helmet with found helmet
		if (yesButton.getComponent<ButtonComponent>().press)
		{
			equipEdit(0, treasure->name, treasure->atk, treasure->def, treasure->element);
		}
		//If in the store, returns store buttons
		if (storeMode)
		{
			moveObjects(2);
		}
		//Removes the treasure menu
		moveObjects(4);
		//Sets yes and no buttons to false to prevent repeated yes and no presses
		noButton.getComponent<ButtonComponent>().press = false;
		yesButton.getComponent<ButtonComponent>().press = false;
	}
	//Player has chance to find chestplates
	else if (type <= 11)
	{
		//Generates a random chestplate
		treasure->chestplate();
		//Writes out the chestplate found
		updStatT("You have found a chestplate! Name: " + treasure->name + " | Defense power: " + to_string(treasure->def) + " | Equip it?", 
			200, 400, 200);
		//Writes out the chestplate the player currently has
		updExtraT("Your current chestplate: " + player->equipment[1]->name + " | Defense power: " + to_string(player->equipment[1]->def), 
			200, 400, 200);
		//Moves the treasure menu onto screen
		moveObjects(5);
		//Wait for the yes or no key to be pressed
		itemLoop();
		//If the yes button is pressed, replace current chestplate with found chestplate
		if (yesButton.getComponent<ButtonComponent>().press)
		{
			equipEdit(1, treasure->name, treasure->atk, treasure->def, treasure->element);
		}
		//If in the store, returns store buttons
		if (storeMode)
		{
			moveObjects(2);
		}
		//Removes the treasure menu
		moveObjects(4);
		//Sets yes and no buttons to false to prevent repeated yes and no presses
		noButton.getComponent<ButtonComponent>().press = false;
		yesButton.getComponent<ButtonComponent>().press = false;
	}
	//Player has chance to find gloves
	else if (type <= 13)
	{
		//Generates a random pair of gloves
		treasure->gloves();
		//Writes out the gloves found
		updStatT("You have found gloves! Name: " + treasure->name + " | Defense power: " + to_string(treasure->def) + " | Equip it?", 
			200, 400, 200);
		//Writes out the gloves the player currently has
		updExtraT("Your current gloves: " + player->equipment[2]->name + " | Defense power: " + to_string(player->equipment[2]->def), 
			200, 400, 200);
		//Moves the treasure menu onto screen
		moveObjects(5);
		//Wait for the yes or no key to be pressed
		itemLoop();
		//If the yes button is pressed, replace current weapon gloves found gloves
		if (yesButton.getComponent<ButtonComponent>().press)
		{
			equipEdit(2, treasure->name, treasure->atk, treasure->def, treasure->element);
		}
		//If in the store, returns store buttons
		if (storeMode)
		{
			moveObjects(2);
		}
		//Removes the treasure menu
		moveObjects(4);
		//Sets yes and no buttons to false to prevent repeated yes and no presses
		noButton.getComponent<ButtonComponent>().press = false;
		yesButton.getComponent<ButtonComponent>().press = false;
	}
	//Player has chance to find boots
	else if (type <= 15)
	{
		//Generates a random pair of boots
		treasure->boots();
		//Writes out the boots found
		updStatT("You have found boots! Name: " + treasure->name + " | Defense power: " + to_string(treasure->def) + " | Equip it?", 
			200, 400, 200);
		//Writes out the boots the player currently has
		updExtraT("Your current boots: " + player->equipment[3]->name + " | Defense power: " + to_string(player->equipment[3]->def),
			200, 400, 200);
		//Moves the treasure menu onto screen
		moveObjects(5);
		//Wait for the yes or no key to be pressed
		itemLoop();
		//If the yes button is pressed, replace current boots with found boots
		if (yesButton.getComponent<ButtonComponent>().press)
		{
			equipEdit(3, treasure->name, treasure->atk, treasure->def, treasure->element);
		}
		//If in the store, returns store buttons
		if (storeMode)
		{
			moveObjects(2);
		}
		//Removes the treasure menu
		moveObjects(4);
		//Sets yes and no buttons to false to prevent repeated yes and no presses
		noButton.getComponent<ButtonComponent>().press = false;
		yesButton.getComponent<ButtonComponent>().press = false;
	}
	//Player has chance to find runes
	else if (type <= 17)
	{
		//Generates a random rune
		treasure->secHand();
		//Writes out the rune found
		updStatT("You have found a rune! Name: " + treasure->name + " Equip it?", 100, 400, 200);
		//Writes out the rune the player currently has
		updExtraT("Your current rune: " + player->equipment[4]->name, 100, 400, 200);
		//Moves the treasure menu onto screen
		moveObjects(5);
		//Wait for the yes or no key to be pressed
		itemLoop();
		//If the yes button is pressed, replace current rune with found rune
		if (yesButton.getComponent<ButtonComponent>().press)
		{
			equipEdit(4, treasure->name, treasure->atk, treasure->def, treasure->element);
		}
		//If in the store, returns store buttons
		if (storeMode)
		{
			moveObjects(2);
		}
		//Removes the treasure menu
		moveObjects(4);
		//Sets yes and no buttons to false to prevent repeated yes and no presses
		noButton.getComponent<ButtonComponent>().press = false;
		yesButton.getComponent<ButtonComponent>().press = false;
	}
	//Player has a low chance to find a gem
	else if (type <= 18)
	{
		//Generates a random gem 
		gold += treasure->gem();
		//Writes out the gem found
		updStatT("You have found an expensive " + treasure->name + "! You sell it for " + to_string(treasure->amount) + " gold!", 200, 400, 200);
		//Updates the gold text to be the new amount of gold
		updGoldT();
		//Opens the treasure menu for gems
		setPos(&statsText, 200, 100);
		setPos(&yesButton, 350, 550);
		//Waits for the yes button to be pressed
		itemLoop();
		//If in the store, returns store buttons
		if (storeMode)
		{
			moveObjects(2);
		}
		//Removes the treasure menu
		moveObjects(4);
		//Sets yes button to false to prevent repeated yes presses
		yesButton.getComponent<ButtonComponent>().press = false;
	}
	//If the parsed number is not within the boundaries, returns an error
	else
	{
		cout << "Error";
	}
}

//Function that re-calculates the player's stats
void refreshHero()
{
	//Resets the character's stats
	player->setAtk();
	player->setDef();
	player->setHp();
	player->setSpd();
	//Resets the player's speed to their max speed
	currentSpeed = player->speed;
}

//Function that initializes the player's equipment
void createPlayer()
{
	//Refreshes equipment...
	equipEdit(0, "Leather Helmet", 0, 5, 0);
	equipEdit(1, "Leather Chestplate", 0, 10, 0);
	equipEdit(2, "Leather Gloves", 0, 5, 0);
	equipEdit(3, "Leather Boots", 0, 5, 0);
	equipEdit(4, "None", 0, 0, 0);
	equipEdit(5, "Wooden Sword", 10, 0, 0);
	//...then re-calculate player's stats
	refreshHero();
}

//Sets up the enemy's stats for the upcoming fight
void createEnemy(int level, int x, int y, int h, int w, string texture)
{
	//If it's the player's first fight in the game, sets the fight to be an easier enemy
	if (firstFight)
	{
		//Sets enemy's level and stats
		enemy->level = level;
		enemy->health = (100 * level) - 20;
		enemy->def = (15 * level) - 2;
		enemy->atk = (50 * level) - 10;
		enemy->speed = 10;
		//Sets the enemy's image and image size
		setSize(&slime, w, h);
		slime.getComponent<SpriteComponent>().setTex(&texture[0]);
		//Sets the enemy's position
		setPos(&slime, x, y);
		//Sets the enemy's button size
		slime.getComponent<ButtonComponent>().width = w;
		slime.getComponent<ButtonComponent>().height = h;
	}
	//Otherwise, creates a random enemy based on the number parsed
	else
	{
		//Sets enemy's level and stats
		enemy->level = level;
		//Sets the enemy's image and image size
		enemy->health = (100 * level) + 10 * (rand() % (2 + level));
		enemy->def = (15 * level) + (rand() % (2 + level) - (2 + level));
		enemy->atk = (50 * level) + 20 * (rand() % (2 + level));
		enemy->speed = 10;
		//Sets the enemy's image and image size
		setSize(&slime, w, h);
		slime.getComponent<SpriteComponent>().setTex(&texture[0]);
		//Sets the enemy's position
		setPos(&slime, x, y);
		//Sets the enemy's button size
		slime.getComponent<ButtonComponent>().width = w;
		slime.getComponent<ButtonComponent>().height = h;
	}
}

//A small function for setting up the health bars in the game's battle sequences
void healthSet()
{
	//Moves bars into place
	moveObjects(9);
	//Updates player health bar
	updExtraT(to_string(player->health) + " / " + to_string(playerH), 400, 200, 50);
	//Updates enemy health bar
	updStatT(to_string(enemy->health) + " / " + to_string(enemyH), 400, 200, 50);
}

//Function that sets up the battle screen
void battleStart(int type)
{
	//Resets player's stats
	refreshHero();
	//If it is the player, first fight in the game, creates the easier enemy
	if (firstFight)
	{	
		createEnemy(1, 300, 200, 256, 256, "Assets/Slime1(TG).png");
		//Indicates the player has had their first fight
		firstFight = false;
	}
	//Otherwise, generates enemies of random difficulty. Level 1 enemy is more likely to show up,
	//then the level 2 enemy, and the level 3 enemy has the lowest chance
	else
	{
		if (type <= 3)
		{
			//Level 1 enemy
			createEnemy(1, 300, 200, 256, 256, "Assets/Slime1(TG).png");
		}
		else if (type <= 5)
		{
			//Level 2 enemy
			createEnemy(2, 300, 200, 256, 256, "Assets/Slime2(TG).png");
		}
		else if (type == 6)
		{
			//Level 3 enemy
			createEnemy(3, 160, 100, 448, 448, "Assets/Slime3(TG).png");
		}
		//If number entered is unknown, make a level 1 enemy
		else
		{
			createEnemy(1, 300, 200, 256, 256, "Assets/Slime1(TG).png");
		}
	}
	//Make background the colosseum
	field.getComponent<SpriteComponent>().setTex("Assets/Arena(TG).png");
	//Get rid of the locations from the screen
	moveObjects(0);
	//Indicate the player is in a battle
	fightMode = true;
	//Sets up max health for health bars
	playerH = player->health;
	enemyH = enemy->health;
	//Sets health bars into play and with health values
	healthSet();
}

//Function that ends the battle
void Game::battleEnd()
{
	//Indicates the player has left the fight
	fightMode = false;
	//Moves the enemy and pause button from the screen
	setPos(&slime, -1000, -1000);
	setPos(&pauseButton, -1000, -1000);
	//Move health bars from screen
	moveObjects(10);
	//If the player wins the fight...
	if (battleWin)
	{
		//Generate (enemy level x 2) number of random treasures for the player to earn
		for (int i = 0; i < (enemy->level * 2); i++)
		{
			random = rand() % 18 + 1;
			generateTreas(random);
		}
	}
	//Return pause button to screen
	setPos(&pauseButton, 0, 0);
	//Gets rid of all battle object and returns main screen locations
	moveObjects(1);
	//Sets background to be the field
	field.getComponent<SpriteComponent>().setTex("Assets/Field(TG).png");
}

//Function for controlling the store purchases
void Game::purchase(int treas)
{
	//If the player has enough gold...
	if (gold >= 100)
	{
		//Pay the gold
		gold -= 100;
		//Update the gold text
		updGoldT();
		//Move the store buttons off the screen
		moveObjects(3);
		//Generate a random treasure based on what store button was clicked
		generateTreas(treas);
	}
}

//Function for controlling the pause menu
void loadPage()
{
	//If on the first page...
	if (pageNum == 0)
	{
		//Show the player's overall stats
		updStatT("Overall Stats  Health: " + to_string(player->health) + "  Attack: " + to_string(player->atk) + "  Defense: "
			+ to_string(player->def) + "  Speed: " + to_string(player->speed), 100, 400, 300);
	}
	//If on the second page...
	else if (pageNum == 1)
	{
		//Show the player's weapon
		updStatT("Name: " + player->equipment[5]->name + " | Attack Power: " + to_string(player->equipment[5]->atk), 
			150, 400, 300);
	}
	//If on the third page...
	else if (pageNum == 2)
	{
		//Shows the player's rune
		updStatT("Rune: " + player->equipment[4]->name, 100, 400, 300);
	}
	//If on any other page of the pause menu...
	else
	{
		//Show the armor equipment in descending order (from helmet to boots)
		updStatT("Name: " + player->equipment[pageNum - 3]->name + " | Defense Power: " + to_string(player->equipment[pageNum - 3]->def),
			150, 400, 300);
	}
}

//Function that controls what all of the buttons do
void Game::buttonControl()
{
	//If the pause button is pressed...
	if (pauseButton.getComponent<ButtonComponent>().press)
	{
		//If the player isn't in a fight...
		if (!fightMode)
		{
			//Re-calculate and refresh the player's stats
			refreshHero();
		}
		//Move health bars from screen if they are out
		moveObjects(10);
		//Set page to first page
		pageNum = 0;
		//Load the pause menu page
		loadPage();
		//Open up the pause menu
		moveObjects(7);
		//Remove locations from screen
		moveObjects(0);
		//Set button to false to prevent infinite clicking
		pauseButton.getComponent<ButtonComponent>().press = false;
	}

	//If the resume button is pressed...
	if (resumeButton.getComponent<ButtonComponent>().press)
	{
		//Remove the pause menu from the screen
		moveObjects(4);
		//If in a fight...
		if (fightMode)
		{
			//Return the enemy to their appropriate place based on which type of enemy it is
			//and then return the pause button to its appropriate place. Also move the next
			//and previous buttons from the screen
			if (enemy->level <= 2)
			{
				//Move enemy
				setPos(&slime, 300, 200);
				//Move pause button
				setPos(&pauseButton, 0, 0);
				//Move next and previous buttons
				setPos(&nextButton, -1000, -1000);
				setPos(&prevButton, -1000, -1000);
				healthSet();
			}
			else
			{
				//Move enemy
				setPos(&slime, 160, 100);
				//Move pause button
				setPos(&pauseButton, 0, 0);
				//Move next and previous buttons
				setPos(&nextButton, -1000, -1000);
				setPos(&prevButton, -1000, -1000);
				healthSet();
			}
		}
		//Otherwise, move all the locations back on screen
		else
		{
			moveObjects(1);
		}
		//Set button to false to prevent infinite clicking
		resumeButton.getComponent<ButtonComponent>().press = false;
	}

	//If the next button is pressed...
	if (nextButton.getComponent<ButtonComponent>().press)
	{
		//If not on the last page of the pause menu...
		if (pageNum < 6)
		{
			//Go to next page
			pageNum++;
			loadPage();
		}
		//Set button to false to prevent infinite clicking
		nextButton.getComponent<ButtonComponent>().press = false;
	}

	//If the previous button is pressed...
	if (prevButton.getComponent<ButtonComponent>().press)
	{
		//If not on first page of the pause menu...
		if (pageNum > 0)
		{
			//Go to previous page
			pageNum--;
			loadPage();
		}
		//Set button to false to prevent infinite clicking
		prevButton.getComponent<ButtonComponent>().press = false;
	}

	//If the colosseum is pressed...
	if (colosseum.getComponent<ButtonComponent>().press)
	{
		//Start a new battle with a random enemy
		random = rand() % 6 + 1;
		battleStart(random);
		//Set button to false to prevent infinite clicking
		colosseum.getComponent<ButtonComponent>().press = false;
	}

	//If the store is pressed...
	if (store.getComponent<ButtonComponent>().press)
	{
		//Indicates the player is in the store
		storeMode = true;
		//Sets background to store background
		field.getComponent<SpriteComponent>().setTex("Assets/StoreInt(TG).png");
		//Removes locations and pause button from screen
		moveObjects(0);
		setPos(&pauseButton, -1000, -1000);
		//Moves store buttons and gold text onto screen
		moveObjects(2);
		//Updates gold text to be the player's current gold amount
		updGoldT();
		//Set button to false to prevent infinite clicking
		store.getComponent<ButtonComponent>().press = false;
	}

	//If the church is pressed...
	if (church.getComponent<ButtonComponent>().press)
	{
		//Opens up the save/reset menu
		updStatT("Do you wish to save or reset?", 100, 400, 200);
		moveObjects(6);
		//Set button to false to prevent infinite clicking
		church.getComponent<ButtonComponent>().press = false;
	}

	//If the reset button is pressed...
	if (resetButton.getComponent<ButtonComponent>().press)
	{
		//Reset's player's gold amount to 100
		gold = 100;
		//Reset's player's first fight to be true
		firstFight = true;
		//Returns to main screen
		moveObjects(1);
		//Reset's player's equipment
		createPlayer();
		//Set button to false to prevent infinite clicking
		resetButton.getComponent<ButtonComponent>().press = false;
	}

	//If the saved button is pressed...
	if (saveButton.getComponent<ButtonComponent>().press)
	{
		//Opens the save menu
		updStatT("You sure you wish to save? Will overwrite old save.", 150, 400, 200);
		moveObjects(8);
		//Set button to false to prevent infinite clicking
		saveButton.getComponent<ButtonComponent>().press = false;
	}

	//If the yes button is pressed (when not on a treasure screen)...
	if (yesButton.getComponent<ButtonComponent>().press)
	{
		//Saves game
		save();
		//Then returns to main screen
		moveObjects(1);
		//Set button to false to prevent infinite clicking
		yesButton.getComponent<ButtonComponent>().press = false;
	}

	//If the no button is pressed (when not on a treasure screen)...
	if (noButton.getComponent<ButtonComponent>().press)
	{
		//Returns to main screen
		moveObjects(1);
		//Set button to false to prevent infinite clicking
		noButton.getComponent<ButtonComponent>().press = false;
	}

	//If the exit button is pressed...
	if (exitButton.getComponent<ButtonComponent>().press)
	{
		//Indicates player has left the store
		storeMode = false;
		//Sets background to field background
		field.getComponent<SpriteComponent>().setTex("Assets/Field(TG).png");
		//Returns to main screen
		moveObjects(1);
		//Gets rid of treasure screen
		moveObjects(3);
		//Set button to false to prevent infinite clicking
		exitButton.getComponent<ButtonComponent>().press = false;
	}

	//If the helmet store button is pressed...
	if (storeButton1.getComponent<ButtonComponent>().press)
	{
		//Attempts to purchase a helmet
		purchase(9);
		//Set button to false to prevent infinite clicking
		storeButton1.getComponent<ButtonComponent>().press = false;
	}

	//If the chestplate store button is pressed...
	if (storeButton2.getComponent<ButtonComponent>().press)
	{
		//Attempts to purchase a chestplate
		purchase(11);
		//Set button to false to prevent infinite clicking
		storeButton2.getComponent<ButtonComponent>().press = false;
	}

	//If the gloves store button is pressed...
	if (storeButton3.getComponent<ButtonComponent>().press)
	{
		//Attempts to purchase a pair of gloves
		purchase(13);
		//Set button to false to prevent infinite clicking
		storeButton3.getComponent<ButtonComponent>().press = false;
	}

	//If the boots store button is pressed...
	if (storeButton4.getComponent<ButtonComponent>().press)
	{
		//Attempts to purchase a pair of boots
		purchase(15);
		//Set button to false to prevent infinite clicking
		storeButton4.getComponent<ButtonComponent>().press = false;
	}

	//If the rune store button is pressed...
	if (storeButton5.getComponent<ButtonComponent>().press)
	{
		//Attempts to purchase a rune
		purchase(17);
		//Set button to false to prevent infinite clicking
		storeButton5.getComponent<ButtonComponent>().press = false;
	}

	//If the weapon store button is pressed...
	if (storeButton6.getComponent<ButtonComponent>().press)
	{
		//Attempts to purchase a weapon
		purchase(7);
		//Set button to false to prevent infinite clicking
		storeButton6.getComponent<ButtonComponent>().press = false;
	}

	//If the slime is pressed...
	if (slime.getComponent<ButtonComponent>().press)
	{
		if (fightMode)
		{
			//Attack the enemy
			enemy->health -= max((player->atk - (player->atk / enemy->def) - enemy->def), 10);
			//Reduce the number of turns the player has left to attack in a row
			currentSpeed -= 10;
			//Health is updated
			healthSet();
			//If the enemy dies...
			if (enemy->health <= 0)
			{
				//End the battle and give the player their treasures
				battleWin = true;
				battleEnd();
			}
		}
		//Set button to false to prevent infinite clicking
		slime.getComponent<ButtonComponent>().press = false;
	}
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	//Value used for the game's fullscreen mode. Currently unused.
	int flags = 0;
	//if (fullscreen)
	//	flags = SDL_WINDOW_FULLSCREEN;

	//Small function that initializes the window and draws the background onto it. Comes with
	//small messages to indicate the progress of the window's creation
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Initialized..." << endl;
		//Creates the actual window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
			cout << "Window created." << endl;
		//Renders what is in the windown
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			//Sets the background of the windown to white
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created." << endl;
		}
		//Finally, shows the game is operational by setting "isRunning" to true
		isRunning = true;
		//Initialize TTF
		TTF_Init();
		//Initialize player
		createPlayer();
		//Initialize all game entities
		initializer();
		//Automatically load saved characer
		load();
		//Randomize the rand seed
		srand(time(0));
	}
	else
	{
		//If initialization fails, sets "isRunning" to false and instantly closes window
		isRunning = false;
	}
}

void Game::update()
{
	//If the player is currently in a fight...
	if (fightMode)
	{
		//And it is the enemy's turn...
		if (currentSpeed == 0)
		{
			//The enemy attacks
			player->health -= max((enemy->atk - (enemy->atk / (player->def / 10)) - player->def), 5);
			//Player's speed is reset
			currentSpeed = player->speed;
			//Health is updated
			healthSet();
			//If the player dies...
			if (player->health <= 0)
			{
				//End the fight without giving the player any treasure
				battleWin = false;
				battleEnd();
			}
		}
	}
	//Refreshes the manager and performs any updates the manager has to perform (mostly
	//just for entity deletion)
	manager.refresh();
	manager.update();
	//Checks if any buttons have been pressed and performs their actions
	buttonControl();
}

//Renders everything in the window every frame
void Game::render()
{
	//Deletes all graphics shown in the window
	SDL_RenderClear(renderer);
	//Renders the entities at their current position
	manager.draw();
	//Shows the rendered graphics in the window
	SDL_RenderPresent(renderer);
}

//Handles the events in the game
void Game::events()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
		//If the X button is clicked...
	case SDL_QUIT:
		//...close the game
		isRunning = false;
		break;

	default:
		break;
	}
}

//Handles the closing of the game
void Game::clean()
{
	//Deletes window
	SDL_DestroyWindow(window);
	//Deletes the render for the window
	SDL_DestroyRenderer(renderer);
	//Quits the program
	SDL_Quit();
}