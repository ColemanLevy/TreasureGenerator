//Header file that creates the Treasure class, which is used to create the random treasure drops in the game
#pragma once

#include "GHeader.h"

//The Treasure class
class Treasure
{
public:
	//Each treasure comes with the following stats. Name, atk, def, and elem are meant to be transferred
	//to the character's equipment. Amount is an integer meant to show in text how much gold is earned from
	//the treasure. Finally, piece is used to indicate which piece of equipment this treasure is replacing
	string name;
	int atk;
	int def;
	int element;
	int piece;
	int amount;

	//All of the functions that creates the treasure they are named after. Most are self-explanatory,
	//and secHand creates Runes
	int gold();
	void weapon();
	void helmet();
	void chestplate();
	void gloves();
	void boots();
	void secHand();
	int gem();
};