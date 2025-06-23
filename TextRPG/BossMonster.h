#pragma once
#include "Item.h"
#include <string>

using namespace std;


class BossMonster
{
public:
	string name;
	int health;
	int attack;

	BossMonster(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	Item* dropItem();
};