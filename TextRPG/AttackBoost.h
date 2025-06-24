#pragma once
#include "Item.h"
class AttackBoost : public Item
{
private:
	std::string Name;
	int AttackIncrease;
	int Price;

public:
	AttackBoost();
	
	void Use(Character* character) override;
	std::unique_ptr<Item> Clone() const override;
};