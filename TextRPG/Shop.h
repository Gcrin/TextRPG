#pragma once
#include<vector>
#include<memory>

class Item;
class Character;

class Shop
{
private:
    std::vector<std::unique_ptr<Item>> AvailableItems;

public:
    Shop();
    ~Shop();

    void DisplayItems() const;
    void BuyItem(int index, Character* player);
    void SellItem(int index, Character* player);
    void AddItem(std::unique_ptr<Item> item);
};
