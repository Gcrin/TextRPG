#pragma once
#include "Monster.h"

class Goblin : public Monster 
{
public:
	Goblin(int level);
	~Goblin() override = default;
	
	std::unique_ptr<Item> DropItem() override;
	int GetGold()  override;
};