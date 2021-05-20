//The header file used to create class for the Main Character (the player) and maintain all of the player's equipment
#pragma once

#include "GHeader.h"

//The class for the Elements of each equipment in the game. Elements provide boosts to the player's stats
//stacking with the more elemental equipment the player has
class Element
{
public:
	//Element types: 1 = Fire, 2 = Earth, 3 = Water, 4 = Wind, 5 = Lightning
	int type = 0;

	//Stats: 0 = Def, 1 = Atk, 2 = Spd, 3 = Health
	double powerUp(int stat) 
	{
		//A switch case that uses the element the equipment has 
		switch (type)
		{
		//If the curent equipment has no element, make no changes to player stats
		case 0:
			if (stat > 1)
				return 0;
			else
				return 1;
			break;
		//If the curent equipment has the fire element, multiply atk by 1.2 and make no 
		//changes to any other stats
		case 1:
			if (stat == 1)
				return 1.2;
			else if (stat > 1)
				return 0;
			else
				return 1;
			break;
		//If the curent equipment has the earth element, make no changes to any stats since the earth element
		//affects only the equipment itself
		case 2:
			if (stat > 1)
				return 0;
			else
				return 1;
			break;
		//If the curent equipment has the water element, increase health by 50 and make no 
		//changes to any other stats
		case 3:
			if (stat == 3)
				return 50;
			else if (stat < 2)
				return 1;
			else
				return 0;
			break;
		//If the curent equipment has the wind element, multiply def by 1.2 and make no 
		//changes to any other stats
		case 4:
			if (stat == 0)
				return 1.2;
			else if (stat > 1)
				return 0;
			else
				return 1;
			break;
		//If the curent equipment has the lightning element, increase speed by 10 and make no 
		//changes to any other stats
		case 5:
			if (stat == 2)
				return 10;
			else if (stat < 2)
				return 1;
			else
				return 0;
			break;
		//If the element on the armor is somehow not any of these, just return 0 as an error
		default:
			return 0;
			break;
		}
	}
};

//The equipment class
class Equipment
{
public:
	//This class maintains a name, attack power, defense power, and element for each equipment item
	string name;
	int atk = 0;
	int def = 0;
	Element* element = new Element();
};

//The class for the player's stats and equipment
class Character
{
public:
	//The character's equipment.
	//Goes in this orfer: Helmet, Chestplate, Gloves, Boots, Second Hand (Can be weapon or shield), and Main Weapon.
	Equipment* equipment[6] = { new Equipment(), new Equipment(), new Equipment(), new Equipment(), new Equipment(), new Equipment() };
	//The character's attack is made from the weapon
	int atk = equipment[5]->atk;
	//The character's defense is made up of the defense power from all the armor
	int def = equipment[0]->def + equipment[1]->def + equipment[2]->def + equipment[3]->def;
	//The player's base health and speed stats
	int speed = 10;
	int health = 100;
	//Note: Although all of the player's stats are initialized this ways, the players stats are actually maintained
	//by the "set" functions. These initializers are just meant to show where the base stats are meant to come from

	//Function that re-calculates the player's defense
	void setDef()
	{
		//Sets base defense to 0
		def = 0;
		//Adds defense power from each equipment is added up to create the player's defense
		for (int i = 0; i < 6; i++)
		{
			def += equipment[i]->def;
		}
		//Every wind element equipment increases the player's defense stat. Stacks exponentially
		for (int i = 0; i < 6; i++)
		{
			def *= equipment[i]->element->powerUp(0);
		}
	}

	//Function that recalculates the player's attack
	void setAtk()
	{
		//Sets base attack to 0
		atk = 0;
		//Adds attack power from each equipment is added up to create the player's attack
		for (int i = 0; i < 6; i++)
		{
			atk += equipment[i]->atk;
		}
		//Every fire element equipment increases the player's attack stat. Stacks exponentially
		for (int i = 0; i < 6; i++)
		{
			atk *= equipment[i]->element->powerUp(1);
		}
	}

	//Function that recalculates the player's speed
	void setSpd()
	{
		//Sets base speed to 10
		speed = 10;
		//Every lightning element equipment increases the player's speed stat. Stacks linearly
		for (int i = 0; i < 6; i++)
		{
			speed += equipment[i]->element->powerUp(2);
		}
	}

	//Function that recalculates the player's health
	void setHp()
	{
		//Sets base health to 100
		health = 100;
		//Every water element equipment increases the player's health stat. Stacks linearly
		for (int i = 0; i < 6; i++)
		{
			health += equipment[i]->element->powerUp(3);
		}
	}
};

