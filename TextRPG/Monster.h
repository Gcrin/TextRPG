#ifndef MONSTER_H
#define MONSTER_H
#include <string>
using namespace std;

class Monster 
{
protected:
    string name;
    int health;
    int attack;

public:
    Monster(const string& name, int health, int attack);
    virtual ~Monster() = default;

    virtual string getName() const;
    virtual int getHealth() const;
    virtual int getAttack() const;
    virtual void takeDamage(int damage);
};

class Goblin : public Monster 
{
public:
    Goblin(int level);
};

class Orc : public Monster 
{
public:
    Orc(int level);
};

class Skeleton : public Monster 
{
public:
    Skeleton(int level);
};

class Slime : public Monster 
{
public:
    Slime(int level);
};

class Boss : public Monster 
{
public:
    Boss(int level);
};

#endif