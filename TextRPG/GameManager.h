#pragma once
#include"Monster.h"
#include"BossMonster.h"
#include "Character.h"

class GameManager
{
public:
    Monster* genderateMonster(int level);
    BossMonster* genderateBossMonster(int level);
    void battle(Character* player);
    void visitShop(Character* player);
    void displayInventory(Character* player);
};
