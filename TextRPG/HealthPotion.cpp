#include "HealthPotion.h"
#include "Character.h"

#include <iostream>


void HealthPotion::use(Character& character)
{
    character.heal(healthRestore);
    std::cout << character.getName() << "��(��) " << getName() << "��(��) ����߽��ϴ�. ü�� " << healthRestore << " ȸ��!\n";
}