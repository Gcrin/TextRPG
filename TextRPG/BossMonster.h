#pragma once
#include "Monster.h"

class BossMonster : public Monster
{
public:
	BossMonster(int level);
	~BossMonster() override = default;

	std::unique_ptr<Item> DropItem() override;
	int GetGold()  override;


};