#include "BossMonster.h"
#include "Item.h"

BossMonster::BossMonster(int level) 
	: Monster("Dragon", level * 45, level * 1, 0)
{

}

std::unique_ptr<Item> BossMonster::DropItem()
{
	return nullptr;
}

int BossMonster::GetGold()
{
	return 0;
}


