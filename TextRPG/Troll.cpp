#include "Troll.h"
#include "Item.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "Util.h"
#include <iostream>

Troll::Troll(int level)
	: Monster("Troll", level * 25, level * 10, 100)
{

}

int Troll::GetGold()
{
	return RandomUtil::GetRandomInt(10, 20);
}

std::unique_ptr<Item> Troll::DropItem()
{

	int roll = RandomUtil::GetRandomInt(1, 100);
	if (roll <= 20)
	{
		int itemTypeDist = RandomUtil::GetRandomInt(0, 1);
		if (itemTypeDist == 0)
		{
			std::cout << GetName() << "이 HealthPotion을 드랍.\n";
			return std::make_unique<HealthPotion>();
		}
		else if (itemTypeDist == 1)
		{
			std::cout << GetName() << "이 AttackBoost를 드랍.\n";
			return std::make_unique<AttackBoost>();
		}

	}
	return nullptr;
}