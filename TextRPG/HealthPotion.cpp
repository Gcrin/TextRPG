#include "HealthPotion.h"
#include <iostream>
#include "Character.h"

void HealthPotion::use(Character& character)
{
    character.heal(healthRestore);
    std::cout << character.getName() << "이(가) " << getName() << "을(를) 사용했습니다. 체력 " << healthRestore << " 회복!\n";
}
