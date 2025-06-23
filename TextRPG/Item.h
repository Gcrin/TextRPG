#pragma once
#include <string>
#include <memory>

class Character;

class Item
{
public:
    virtual ~Item() = default;
    virtual std::string GetName() = 0;
    virtual int GetPrice() = 0;
    virtual void Use(Character* Character) = 0;
    virtual std::unique_ptr<Item> Clone() const = 0;
};
