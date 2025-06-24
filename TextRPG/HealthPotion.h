#pragma once
#include "Item.h"
class HealthPotion : public Item
{
private:
	int HealthRestore;

public:
	HealthPotion();

	void Use(Character* character) override;
	std::unique_ptr<Item> Clone() const override;
};