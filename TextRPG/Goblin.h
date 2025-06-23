#pragma once
#include "Item.h"
#include <string>

using namespace std;


class Goblin
{
public:
	string name;
	int health;
	int attack;

	Goblin(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	Item* dropItem();
};