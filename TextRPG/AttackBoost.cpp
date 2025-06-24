#include "AttackBoost.h"
#include "Character.h"
#include <iostream>

AttackBoost::AttackBoost()
	: Item(ItemID::AttackBoost, "AttackBoost", 50), AttackIncrease(10), Price(50)
{

}

void AttackBoost::Use(Character* character)
{
	std::cout << this->GetName() << "!!!";
	character->IncreaseAttack(AttackIncrease);
}

std::unique_ptr<Item> AttackBoost::Clone() const
{
	return std::make_unique<AttackBoost>(*this);
}
