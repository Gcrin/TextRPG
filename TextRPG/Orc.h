#pragma once
#include "Monster.h"

class Orc : public Monster
{
public:
	Orc(int level);
	~Orc() override = default;

	std::unique_ptr<Item> DropItem() override;
	int GetGold()  override;

};