#include "Orc.h"
#include "Item.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "Util.h"
#include <iostream>

Orc::Orc(int level)
	: Monster("Orc", level * 30, level * 5, 80)
{

}

int Orc::GetGold()
{
	return RandomUtil::GetRandomInt(10, 20);
}

std::unique_ptr<Item> Orc::DropItem()
{

	int roll = RandomUtil::GetRandomInt(1, 100);
	if (roll <= 10)
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

