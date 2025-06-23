#pragma once
#include "Monster.h"
#include <random>

class Goblin : public Monster 
{
private:
	std::string Name;
	int Health;
	int Attack;
	int Experience;

	std::mt19937& randomEngine;
	
public:
	Goblin(int level, std::mt19937& engine);
	~Goblin() override = default;

	std::string GetName() const override { return Name; }
	int GetHealth() const override { return Health; }
	int GetAttack() const override { return Attack; }
	int GetExperience() const override { return Experience; }
	int GetGold()  override;
	
	void TakeDamage(int damage) override;
	std::unique_ptr<Item> DropItem() override;

};