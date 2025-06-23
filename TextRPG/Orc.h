#pragma once
#include "Item.h"
#include <string>

using namespace std;


class Orc
{
public:
	string name;
	int health;
	int attack;

	Orc(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	Item* dropItem();
};