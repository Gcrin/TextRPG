#pragma once
#include <string>
#include <memory>

class Item;

class Monster
{
public:
    virtual ~Monster() = default;

    virtual std::string GetName() const = 0;
    virtual int GetHealth() const = 0;
    virtual int GetAttack() const = 0;
    virtual void TakeDamage(int damage) = 0;
    virtual std::unique_ptr<Item> DropItem() = 0;
    virtual int GetGold()  = 0;
    virtual int GetExperience() const = 0;
};
