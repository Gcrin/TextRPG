#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <memory>
#include <string>

#include "Shop.h"
#include "Character.h"

using namespace std;

class GameManager {
private:
    unique_ptr<Character> player;
    Shop shop;
    unique_ptr<class Monster> generateMonster(int level);

public:
    void createCharacter(const string& name);
    void battle();
    void run();
};

#endif