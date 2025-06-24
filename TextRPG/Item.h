#pragma once
#include "Enums.h"
#include <string>
#include <memory>



class Character;

class Item
{
protected:
    std::string Name;
    int Price;
    ItemID ID;

public:
    Item(ItemID id, std::string name, int price);
    virtual ~Item() = default;

    virtual void Use(Character* Character) = 0;
    virtual std::unique_ptr<Item> Clone() const = 0;

    virtual ItemID GetId() const { return ID; }
    virtual std::string GetName() const { return Name; }
    virtual int GetPrice() const { return Price; }
};
