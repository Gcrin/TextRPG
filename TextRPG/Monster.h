#pragma once
#include <memory>
#include <string>

class Item;

class Monster
{
public:
    Monster(std::string name, int playerLevel, float healthMultiplier = 1.f, float attackMultiplier = 1.f);
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
    Goblin(int playerLevel) : Monster("Goblin", playerLevel)
    {
    }
};

class Orc : public Monster
{
public:
    Orc(int playerLevel) : Monster("Orc", playerLevel)
    {
    }
};

class Skeleton : public Monster
{
public:
    Skeleton(int playerLevel) : Monster("Skeleton", playerLevel)
    {
    }
};

class Slime : public Monster
{
public:
    Slime(int playerLevel) : Monster("Slime", playerLevel)
    {
    }
};

class BossMonster : public Monster
{
public:
    BossMonster(int playerLevel)
        : Monster("Dragon",
                  playerLevel, 1.5f, 1.5f)
    {
    }

    std::unique_ptr<Item> dropItem() override
    {
        // 보스는 아이템 드랍 안함 (게임 클리어)
        return nullptr;
    }
};
