#include "HealthPotion.h"
#include "Character.h"
#include <iostream>

HealthPotion::HealthPotion() 
	: Item(ItemID::HealthPotion,"HealthPotion", 30), HealthRestore(100)
{
}

void HealthPotion::Use(Character* character)
{
	if (character->GetHealth() == character->GetMaxHealth())
	{
		std::cout << "캐릭터의 체력이 이미 최대입니다.\n";
		return;
	}
	
	std::cout << this->GetName() << "~~~";
	character->RestoreHealth(HealthRestore);
}

std::unique_ptr<Item> HealthPotion::Clone() const
{
	return std::make_unique<HealthPotion>(*this);
}
