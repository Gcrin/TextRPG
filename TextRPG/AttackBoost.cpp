#include "AttackBoost.h"
#include <iostream>
#include "Character.h"

void AttackBoost::use(Character& character)
{
    character.increaseAttack(attackIncrease);
    std::cout << character.getName() << "이(가) " << getName() << "을(를) 사용했습니다. 공격력 " << attackIncrease << " 증가!\n";
}
