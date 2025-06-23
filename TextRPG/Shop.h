#pragma once
#include "Item.h"
#include <string>
#include <vector>
#include <Character.h>

using namespace std;

class Shop
{
public:
    vector<Item*> availableItems;

    Shop();
    void displayItem();
    void buyItem(int index, Character* player);
    void sellItem(int index, Character* player);
};
