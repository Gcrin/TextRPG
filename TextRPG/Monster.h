#pragma once
#include "Item.h"
#include <string>

using namespace std;

class Monster
{
public:
    virtual string getName() = 0;
    virtual int getHealth() = 0;
    virtual int getAttack() = 0;
    virtual void takeDamage(int damage) = 0;
    virtual Item* dropItem() = 0;
    virtual ~Monster() {}
};

class Goblin : public Monster
{
	string name = "Goblin";
	int health;
	int attack;

	Goblin(int level);
	string getName() override;
	int getHealth() override;
	int getAttack() override;
	void takeDamage(int damage) override;
	Item* dropItem() override;
};
