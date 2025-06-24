#pragma once
#include <memory>
#include <string>

class Item;

class Monster
{
public:
    Monster(std::string name, int playerLevel, float attackMultiplier = 1.f, float healthMultiplier = 1.f);
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
    Goblin(int playerLevel) : Monster("고블린",playerLevel)
    {
    }
};

class Orc : public Monster
{
public:
    Orc(int playerLevel) : Monster("오크", playerLevel)
    {
    }
};

class Troll : public Monster
{
public:
    Troll(int playerLevel) : Monster("트롤", playerLevel)
    {
    }
};

class Slime : public Monster
{
public:
    Slime(int playerLevel) : Monster("슬라임", playerLevel)
    {
    }
};

class BossMonster : public Monster
{
public:
    BossMonster(int playerLevel)
        : Monster("보스 드래곤",
                  playerLevel, 1.5f, 1.5f)
    {
    }

    std::unique_ptr<Item> dropItem() override
    {
        // 보스는 아이템 드랍 안함 (게임 클리어)
        return nullptr;
    }
};
