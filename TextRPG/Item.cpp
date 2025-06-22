#include "Item.h"
#include "Character.h"
#include "GameManager.h"
#include <iostream>

unique_ptr<Item> Item::createRandomItem() 
{
    GameManager* gm = GameManager::getInstance();

    if (gm->getRandomChance(50)) 
    {
        return make_unique<HealthPotion>();
    }
    else 
    {
        return make_unique<AttackBoost>();
    }
}

void HealthPotion::use(Character* character)
{
    if (character == nullptr)
    {
        cout << "캐릭터가 유효하지 않습니다!" << endl;
        return;
    }

    cout << name << " 사용! 체력을 " << healthRestore << " 회복합니다." << endl;
    character->heal(healthRestore);
}

void AttackBoost::use(Character* character)
{
    if (character == nullptr)
    {
        cout << "캐릭터가 유효하지 않습니다!" << endl;
        return;
    }

    cout << name << " 사용! 공격력이 " << attackIncrease << " 추가로 증가합니다." << endl;

    character->addAdditionalAttackAmount(attackIncrease);
}