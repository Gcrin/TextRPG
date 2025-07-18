#pragma once
#include <memory>
#include <vector>

class Character;
class Item;

class Shop
{
public:
    Shop();
    void displayShopItems()  const;
    void displayShop(Character& character) const;
    void buyItem(int itemIndex, Character& character);
    void sellItem(int itemIndex, Character& character);
    size_t getItemCount() const;


private:
    std::vector<std::unique_ptr<Item>> items;

};