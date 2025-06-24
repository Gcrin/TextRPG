#include "Goblin.h"
#include "Item.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "Util.h"
#include <iostream>

Goblin::Goblin(int level)
	: Monster("Goblin", level * 20, level * 5, 1000)
{
	
}

int Goblin::GetGold()
{
	return RandomUtil::GetRandomInt(10, 20);
}

std::unique_ptr<Item> Goblin::DropItem()
{
	
	int roll = RandomUtil::GetRandomInt(1, 100);
	if (roll<=5)
	{
		int itemTypeDist = RandomUtil::GetRandomInt(0, 1);
		if (itemTypeDist == 0)
		{
			std::cout << GetName() <<"이 HealthPotion을 드랍.\n";
			return std::make_unique<HealthPotion>();
		}
		else if(itemTypeDist == 1)
		{
			std::cout << GetName() <<"이 AttackBoost를 드랍.\n";
			return std::make_unique<AttackBoost>();
		}
		
	}
	return nullptr;
}
