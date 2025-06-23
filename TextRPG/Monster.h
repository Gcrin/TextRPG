#pragma once
#include <string>
#include "Item.h"

class Monster {
protected:
    std::string name;
    int health, attack;

public:
    Monster(std::string name, int hp, int atk);
    virtual ~Monster() = default;

    std::string getName() const;
    int getHealth() const;
    int getAttack() const;
    void takeDamage(int damage);
    bool isAlive() const;
    virtual Item* dropItem();
};

class Goblin : public Monster {
public:
    Goblin(int level);
};

class Slime : public Monster {
public:
    Slime(int level);
};

class Orc : public Monster {
public:
    Orc(int level);
};

class Skeleton : public Monster {
public:
    Skeleton(int level);
};

class BossMonster : public Monster {
public:
    BossMonster(int level);
};

