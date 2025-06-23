#pragma once
#include <vector>
#include "Item.h"
#include "Character.h"

class Shop {
private:
    std::vector<Item*> items;
    std::vector<int> prices;

public:
    Shop();
    void displayItems() const;
    void buyItem(int index, Character* player);
    void sellItem(int index, Character* player);
};