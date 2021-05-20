//A small class that controls the stats for enemies
#pragma once

#include "GHeader.h"

//The Enemy class, itself
class Enemy
{
public:
	//The stats contained in any enemy, initialized to 0
	int atk = 0;
	int def = 0;
	int health = 0;
	int speed = 0;
	int level = 0;
};