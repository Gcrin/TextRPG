#pragma once
#include <string>
#include <memory>

class Item;

class Monster
{
protected:
    std::string Name;
    int Health;
    int Attack;
    int Experience;

public:
    Monster(std::string name, int health, int attack, int experience);
    virtual ~Monster() = default;

    virtual void TakeDamage(int damage);
    virtual std::unique_ptr<Item> DropItem() = 0;
    virtual int GetGold()  = 0;

    virtual std::string GetName() const { return Name; }
    virtual int GetHealth() const { return Health; }
    virtual int GetAttack() const { return Attack; }
    virtual int GetExperience() const { return Experience; }

};
