#pragma once
#include "Item.h"
#include <string>

using namespace std;


class Troll
{
public:
	string name;
	int health;
	int attack;

	Troll(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	Item* dropItem();
};