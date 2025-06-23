#pragma once
#include "Item.h"
#include "Shop.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Character
{
public:
    string name;
    int level = 1;
    int health = 200;
    int maxHealth = 200;
    int attack = 30;
    int experience = 0;
    int gold = 0;
    vector<Item*> inventory;

    Character(string name);
    static Character* getInstance (string name = "");
    void displayStatus();
    void levelUp();
    void useItem(int index);
    void visitShop();
};
