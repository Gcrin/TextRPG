#include "AttackBoost.h"
#include <iostream>
#include "Character.h"

void AttackBoost::use(Character& character)
{
    character.increaseAttack(attackIncrease);
    std::cout << character.getName() << "��(��) " << getName() << "��(��) ����߽��ϴ�. ���ݷ� " << attackIncrease << " ����!\n";
}