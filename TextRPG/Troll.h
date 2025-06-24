#pragma once
#include "Monster.h"

class Troll : public Monster
{
public:
	Troll(int level);
	~Troll() override = default;

	std::unique_ptr<Item> DropItem() override;
	int GetGold()  override;
};