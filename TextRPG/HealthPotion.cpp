#include "HealthPotion.h"
#include "Character.h"
#include <iostream>

HealthPotion::HealthPotion() : Name("HealthPotion"), HealthRestore(50), Price(30)
{
}

void HealthPotion::Use(Character* character)
{
	if (character->GetHealth() == character->GetMaxHealth())
	{
		std::cout << "캐릭터의 체력이 이미 최대입니다.\n";
		return;
	}
	
	std::cout << this->GetName() << "사용!!!";
	character->RestoreHealth(HealthRestore);
}

std::unique_ptr<Item> HealthPotion::Clone() const
{
	return std::make_unique<HealthPotion>(*this);
}
