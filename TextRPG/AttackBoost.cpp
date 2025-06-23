#include "AttackBoost.h"
#include "Character.h"
#include <iostream>

AttackBoost::AttackBoost() : Name("AttackBoost"), AttackIncrease(10), Price(50)
{

}

void AttackBoost::Use(Character* character)
{
	std::cout << this->GetName() << "사용!!!";
	character->IncreaseAttack(AttackIncrease);
}

std::unique_ptr<Item> AttackBoost::Clone() const
{
	return std::make_unique<AttackBoost>(*this);
}
