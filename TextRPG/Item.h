#pragma once
#include <string>
#include "Character.h"

class Character;


using namespace std;

class Item
{
public:
	virtual string getName() = 0;
	virtual void use(Character* character) = 0;
	virtual ~Item() {}
};

class HealthPotion : public Item
{
public:
	string name = "HealthPotion";
	int healthRestore = 50;
	string getName() override;
	void use(Character* character) override;
};

class AttackBoost : public Item
{
public:
	string name = "AttackBoost";
	int AttackIncrease;
	string getName() override;
	void use(Character* character) override;
};
