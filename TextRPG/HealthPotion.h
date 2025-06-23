#pragma once
#include "Item.h"
class HealthPotion : public Item
{
private:
	std::string Name;
	int HealthRestore;
	int Price;

public:
	HealthPotion();

	std::string GetName() override { return Name; }
	int GetPrice() override { return Price; }
	void Use(Character* character) override;
	std::unique_ptr<Item> Clone() const override;
};