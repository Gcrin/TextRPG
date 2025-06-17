#pragma once
#include <memory>
#include <string>
#include "Utils.h"

class Item;

class Monster
{
public:
    Monster(std::string name, int health, int attack);
    virtual ~Monster() = default;

    void takeDamage(int damage);

    std::string getName() const { return name; }
    int getHealth() const { return currentHealth; }
    int getAttack() const { return attack; }
    bool isDead() const { return currentHealth <= 0; }

    virtual std::unique_ptr<Item> dropItem();

protected:
    std::string name;
    int currentHealth;
    int attack;
};

class Goblin : public Monster
{
public:
    Goblin(int playerLevel) : Monster("고블린", Utils::getRandomInt(playerLevel * 20, playerLevel * 30),
                                      Utils::getRandomInt(playerLevel * 5, playerLevel * 10))
    {
    }
};

class Orc : public Monster
{
public:
    Orc(int playerLevel) : Monster("오크", Utils::getRandomInt(playerLevel * 20, playerLevel * 30),
                                   Utils::getRandomInt(playerLevel * 5, playerLevel * 10))
    {
    }
};

class Troll : public Monster
{
public:
    Troll(int playerLevel) : Monster("트롤", Utils::getRandomInt(playerLevel * 20, playerLevel * 30),
                                     Utils::getRandomInt(playerLevel * 5, playerLevel * 10))
    {
    }
};

class Slime : public Monster
{
public:
    Slime(int playerLevel) : Monster("슬라임", Utils::getRandomInt(playerLevel * 20, playerLevel * 30),
                                     Utils::getRandomInt(playerLevel * 5, playerLevel * 10))
    {
    }
};
class BossMonster : public Monster {
public:
    BossMonster(int playerLevel)
        : Monster("보스 드래곤", 
                  Utils::getRandomInt(static_cast<int>(playerLevel * 20 * 1.5), static_cast<int>(playerLevel * 30 * 1.5)), 
                  Utils::getRandomInt(static_cast<int>(playerLevel * 5 * 1.5), static_cast<int>(playerLevel * 10 * 1.5))) {}
    
    std::unique_ptr<Item> dropItem() override { // 보스는 아이템 드랍 안함 (게임 클리어)
        return nullptr;
    }
};