#pragma once
#include "Monster.h"

class Orc : public Monster
{
private:
	std::string Name;
	int Health;
	int Attack;

public:
	Orc(int level);
	~Orc() override = default;

	std::string GetName() override { return Name; }
	int GetHealth() override { return Health; }
	int GetAttack() override { return Attack; }

	void TakeDamage(int damage) override;
	Item* DropItem() override;

};