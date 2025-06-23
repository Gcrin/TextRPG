#include "Goblin.h"
#include "Item.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "iostream"
#include <algorithm>

Goblin::Goblin(int level, std::mt19937& engine)
	: Name("Goblin"), Health(level * 20), Attack(level * 5), Experience(50), randomEngine(engine)
{
	
}

int Goblin::GetGold()
{
	std::uniform_int_distribution<int> goldDist(10, 20);
	return goldDist(randomEngine);
}

void Goblin::TakeDamage(int damage)
{
	Health -= damage;
	Health = std::max(Health, 0);
}

std::unique_ptr<Item> Goblin::DropItem()
{
	std::uniform_int_distribution<int> dropDist(1, 100);
	int roll = dropDist(randomEngine);
	if (roll<=10)
	{
		std::uniform_int_distribution<int> itemTypeDist(0, 1);
		if (itemTypeDist(randomEngine) == 0)
		{
			std::cout << GetName() <<"이 HealthPotion을 떨어뜨렸다.\n";
			return std::make_unique<HealthPotion>();
		}
		else
		{
			std::cout << GetName() <<"이 AttackBoost를 떨어뜨렸다.\n";
			return std::make_unique<AttackBoost>();
		}
		
	}
	return nullptr;
}
