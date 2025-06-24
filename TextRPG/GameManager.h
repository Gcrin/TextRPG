#pragma once

#include "Character.h"
#include "Monster.h"

#include <memory>



class GameManager
{
public:
    void Run();

private:
    bool getInputYesNo() const;
    int getInputRangeInt(int min, int max) const;

    void CreatePlayer();
    std::unique_ptr<Monster> CreateMonster();
    void StartBattle();
    void visitShop();

    std::unique_ptr<Character> player = nullptr;
    bool isGameOver = false;
};
