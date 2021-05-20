#include "Headers/Treasure.h"

//The string used as the treasure's name
string naming;
//Int used in most rand()'s
int amnt;
//Int used to keep track of elemnt type
int elem = 0;
//Int used in certain calculations
int material;

//Small function that gives between 1 and 100 gold
int Treasure::gold()
{
	//Randomly creates a number of gold between 1 and 100
	amnt = rand() % 100 + 1;
	//Sets the amount of gold to the amount variable will be used to write out
	//how much gold was found
	amount = amnt;
	return amnt;
}

//Function that gives random weapons along with random stats and elements 
void Treasure::weapon()
{
	//Resets the name of the treasure
	naming = "";
	//Section that determines the material quality of the item. The higher the quality, the less
	//likely to get it
	amnt = rand() % 15 + 1;
	if (amnt <= 5)
	{
		naming += "Wood ";
		material = 0;
	}
	else if (amnt <= 9)
	{
		naming += "Iron ";
		material = 1;
	}
	else if (amnt <= 12)
	{
		naming += "Bronze ";
		material = 2;
	}
	else if (amnt <= 14)
	{
		naming += "Steel ";
		material = 3;
	}
	else if (amnt <= 15)
	{
		naming += "Diamond ";
		material = 4;
	}
	else
	{
		naming += "error ";
		material = 0;
	}
	//Section that determines the weapon found. Normal weapons (without an element) 
	//have a higher chance to be drawn.
	amnt = rand() % 15 + 1;
	if (amnt <= 2)
	{
		naming += "Sword";
		elem = 0;
	}
	else if (amnt <= 4)
	{
		naming += "Spear";
		elem = 0;
	}
	else if (amnt <= 6)
	{
		naming += "Axe";
		elem = 0;
	}
	else if (amnt <= 8)
	{
		naming += "Hammer";
		elem = 0;
	}
	else if (amnt <= 10)
	{
		naming += "Bow";
		elem = 0;
	}
	else if (amnt == 11)
	{
		naming += "Sword of ";
	}
	else if (amnt == 12)
	{
		naming += "Spear of ";
	}
	else if (amnt == 13)
	{
		naming += "Axe of ";
	}
	else if (amnt == 14)
	{
		naming += "Hammer of ";
	}
	else if (amnt == 15)
	{
		naming += "Bow of ";
	}
	else
	{
		naming += "error";
	}
	//Section that gives the item a random element if it has one
	if (amnt > 10 && amnt < 16)
	{
		amnt = rand() % 5 + 1;
		switch (amnt)
		{
		case 1:
			naming += "Fire";
			elem = 1;
			break;

		case 2:
			naming += "Earth";
			material += 1;
			elem = 2;
			break;

		case 3:
			naming += "Water";
			elem = 3;
			break;

		case 4:
			naming += "Wind";
			elem = 4;
			break;

		case 5:
			naming += "Lightning";
			elem = 5;
			break;

		default:
			naming += "error";
			break;
		}
	}
	//Section that gives the actual stats of the item
	amnt = (rand() % 20 + 1) + (material * 20);
	//Section that sets the name, atk, def, and element of the treasure to what
	//has been drawn
	name = naming;
	element = elem;
	atk = amnt;
	def = 0;
}

//Function that gives possible armor along with random stats
void Treasure::helmet()
{
	//Resets the name of the treasure
	naming = "";
	//Section that determines the material quality of the item. The higher the quality, the less
	//likely to get it
	amnt = rand() % 15 + 1;
	if (amnt <= 5)
	{
		naming += "Leather ";
		material = 0;
	}
	else if (amnt <= 9)
	{
		naming += "Iron ";
		material = 1;
	}
	else if (amnt <= 12)
	{
		naming += "Bronze ";
		material = 2;
	}
	else if (amnt <= 14)
	{
		naming += "Steel ";
		material = 3;
	}
	else if (amnt <= 15)
	{
		naming += "Diamond ";
		material = 4;
	}
	else
	{
		naming += "error ";
		material = 0;
	}
	//Section that determines the helmet found. Normal helmets (without an element) 
	//have a higher chance to be drawn.
	amnt = rand() % 3 + 1;
	if (amnt <= 2)
	{
		naming += "Helmet";
		elem = 0;
	}
	else if (amnt == 3)
	{
		naming += "Helmet of ";
	}
	else
	{
		naming += "error";
	}
	//Section that gives the item a random element if it has one
	if (amnt == 3)
	{
		amnt = rand() % 5 + 1;
		switch (amnt)
		{
		case 1:
			naming += "Fire";
			elem = 1;
			break;

		case 2:
			naming += "Earth";
			material += 1;
			elem = 2;
			break;

		case 3:
			naming += "Water";
			elem = 3;
			break;

		case 4:
			naming += "Wind";
			elem = 4;
			break;

		case 5:
			naming += "Lightning";
			elem = 5;
			break;

		default:
			naming += "error";
			break;
		}
	}
	//Section that gives the actual stats of the item
	amnt = (rand() % 20 + 1) + (material * 20);
	//Section that sets the name, atk, def, and element of the treasure to what
	//has been drawn
	name = naming;
	element = elem;
	atk = 0;
	def = amnt;
}

//Function that gives possible armor along with random stats
void Treasure::chestplate()
{
	//Resets the name of the treasure
	naming = "";
	//Section that determines the material quality of the item. The higher the quality, the less
	//likely to get it
	amnt = rand() % 15 + 1;
	if (amnt <= 5)
	{
		naming += "Leather ";
		material = 0;
	}
	else if (amnt <= 9)
	{
		naming += "Iron ";
		material = 1;
	}
	else if (amnt <= 12)
	{
		naming += "Bronze ";
		material = 2;
	}
	else if (amnt <= 14)
	{
		naming += "Steel ";
		material = 3;
	}
	else if (amnt <= 15)
	{
		naming += "Diamond ";
		material = 4;
	}
	else
	{
		naming += "error ";
		material = 0;
	}
	//Section that determines the chestplate found.Normal chestplates (without an element) 
	//have a higher chance to be drawn.
	amnt = rand() % 3 + 1;
	if (amnt <= 2)
	{
		naming += "Chestplate";
		elem = 0;
	}
	else if (amnt == 3)
	{
		naming += "Chestplate of ";
	}
	else
	{
		naming += "error";
	}
	//Section that gives the item a random element if it has one
	if (amnt == 3)
	{
		amnt = rand() % 5 + 1;
		switch (amnt)
		{
		case 1:
			naming += "Fire";
			elem = 1;
			break;

		case 2:
			naming += "Earth";
			material += 1;
			elem = 2;
			break;

		case 3:
			naming += "Water";
			elem = 3;
			break;

		case 4:
			naming += "Wind";
			elem = 4;
			break;

		case 5:
			naming += "Lightning";
			elem = 5;
			break;

		default:
			naming += "error";
			break;
		}
	}
	//Section that gives the actual stats of the item
	amnt = (rand() % 20 + 1) + (material * 20);
	//Section that sets the name, atk, def, and element of the treasure to what
	//has been drawn
	name = naming;
	element = elem;
	atk = 0;
	def = amnt;
}

//Function that gives possible armor along with random stats
void Treasure::gloves()
{
	//Resets the name of the treasure
	naming = "";
	//Section that determines the material quality of the item. The higher the quality, the less
	//likely to get it
	amnt = rand() % 15 + 1;
	if (amnt <= 5)
	{
		naming += "Leather ";
		material = 0;
	}
	else if (amnt <= 9)
	{
		naming += "Iron ";
		material = 1;
	}
	else if (amnt <= 12)
	{
		naming += "Bronze ";
		material = 2;
	}
	else if (amnt <= 14)
	{
		naming += "Steel ";
		material = 3;
	}
	else if (amnt <= 15)
	{
		naming += "Diamond ";
		material = 4;
	}
	else
	{
		naming += "error ";
		material = 0;
	}
	//Section that determines the gloves found. Normal gloves (without an element) 
	//have a higher chance to be drawn.
	amnt = rand() % 3 + 1;
	if (amnt <= 2)
	{
		naming += "Gloves";
		elem = 0;
	}
	else if (amnt == 3)
	{
		naming += "Gloves of ";
	}
	else
	{
		naming += "error";
	}
	//Section that gives the item a random element if it has one
	if (amnt == 3)
	{
		amnt = rand() % 5 + 1;
		switch (amnt)
		{
		case 1:
			naming += "Fire";
			elem = 1;
			break;

		case 2:
			naming += "Earth";
			material += 1;
			elem = 2;
			break;

		case 3:
			naming += "Water";
			elem = 3;
			break;

		case 4:
			naming += "Wind";
			elem = 4;
			break;

		case 5:
			naming += "Lightning";
			elem = 5;
			break;

		default:
			naming += "error";
			break;
		}
	}
	//Section that gives the actual stats of the item
	amnt = (rand() % 20 + 1) + (material * 20);
	//Section that sets the name, atk, def, and element of the treasure to what
	//has been drawn
	name = naming;
	element = elem;
	atk = 0;
	def = amnt;
}

//Function that gives possible armor along with random stats
void Treasure::boots()
{
	//Resets the name of the treasure
	naming = "";
	//Section that determines the material quality of the item. The higher the quality, the less
	//likely to get it
	amnt = rand() % 15 + 1;
	if (amnt <= 5)
	{
		naming += "Leather ";
		material = 0;
	}
	else if (amnt <= 9)
	{
		naming += "Iron ";
		material = 1;
	}
	else if (amnt <= 12)
	{
		naming += "Bronze ";
		material = 2;
	}
	else if (amnt <= 14)
	{
		naming += "Steel ";
		material = 3;
	}
	else if (amnt <= 15)
	{
		naming += "Diamond ";
		material = 4;
	}
	else
	{
		naming += "error ";
		material = 0;
	}
	//Section that determines the boots found. Normal boots (without an element) 
	//have a higher chance to be drawn.
	amnt = rand() % 3 + 1;
	if (amnt <= 2)
	{
		naming += "Boots";
		elem = 0;
	}
	else if (amnt == 3)
	{
		naming += "Boots of ";
	}
	else
	{
		naming += "error";
	}
	//Section that gives the item a random element if it has one
	if (amnt == 3)
	{
		amnt = rand() % 5 + 1;
		switch (amnt)
		{
		case 1:
			naming += "Fire";
			elem = 1;
			break;

		case 2:
			naming += "Earth";
			material += 1;
			elem = 2;
			break;

		case 3:
			naming += "Water";
			elem = 3;
			break;

		case 4:
			naming += "Wind";
			elem = 4;
			break;

		case 5:
			naming += "Lightning";
			elem = 5;
			break;

		default:
			naming += "error";
			break;
		}
	}
	//Section that gives the actual stats of the item
	amnt = (rand() % 20 + 1) + (material * 20);
	//Section that sets the name, atk, def, and element of the treasure to what
	//has been drawn
	name = naming;
	element = elem;
	atk = 0;
	def = amnt;
}

//Function used to randomly generate runes
void Treasure::secHand()
{
	//Resets the name of the treasure
	naming = "";
	//There's only one kind of rune, the kind with an element
	naming += "Rune of ";
	//Assigns a random element to the rune. Does not allow for
	//earth elements since that only affects the material and runes
	//don't have material quality
	amnt = rand() % 4 + 1;
	switch (amnt)
	{
	case 1:
		naming += "Fire";
		elem = 1;
		break;

	case 2:
		naming += "Water";
		elem = 3;
		break;

	case 3:
		naming += "Wind";
		elem = 4;
		break;

	case 4:
		naming += "Lightning";
		elem = 5;
		break;

	default:
		naming += "error";
		break;
	}
	//Section that sets the name, atk, def, and element of the treasure to what
	//has been drawn
	name = naming;
	element = elem;
	atk = 0;
	def = 0;
}

//A function that gives out gems with specific values and possible increased values
int Treasure::gem()
{
	//Resets the name of the treasure
	naming = "";
	//This is used as the multiplier for any items of higher quality
	material = 1;
	//Section that determines if the gem received is "Perfect" which will double its value
	amnt = rand() % 100 + 1;
	if (amnt <= 5)
	{
		material = 2;
		naming += "Perfect ";
	}
	//Section that decides at random what type of gem was found and assigns its value based on this. The more
	//expensive the gem, the less likely to get it
	amnt = rand() % 15 + 1;
	if (amnt <= 5)
	{
		naming += "Ruby";
		material = material * 100;
	}
	else if (amnt <= 9)
	{
		naming += "Sapphire";
		material = material * 150;
	}
	else if (amnt <= 12)
	{
		naming += "Emerald";
		material = material * 200;
	}
	else if (amnt <= 14)
	{
		naming += "Black Opal";
		material = material * 250;
	}
	else if (amnt == 15)
	{
		naming += "Orange Diamond";
		material = material * 300;
	}
	else
	{
		naming += "error";
	}
	//Sets the name and value of the gem to be written out
	name = naming;
	amount = material;
	return material;
}