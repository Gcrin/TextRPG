#pragma once
#include "Character.h"
#include "Monster.h"

class GameManager {
public:
    void start();
    void battle();
    Monster* generateMonster();
};