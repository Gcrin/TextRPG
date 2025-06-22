#pragma once

#include <string>
#include <memory>
using namespace std;

class Monster
{
public:

    Monster(const string& monsterName, int monsterLevel);

    virtual ~Monster() = default;

    virtual void generateStats(int playerLevel) = 0;

    void takeDamage(int damage);
    bool isAlive() const { return health > 0; }

    // 몬스터 정보
    void displayInfo() const;

    // Getter
    string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getLevel() const { return level; }

    static unique_ptr<Monster> createRandomMonster(int playerLevel);

protected:
    string name;
    int health;
    int attack;
    int level;
};

class Goblin : public Monster 
{
public:
    Goblin(int playerLevel);

    virtual void generateStats(int playerLevel) override;
};

class Orc : public Monster
{
public:
    Orc(int playerLevel);

    virtual void generateStats(int playerLevel) override;
};

class Troll : public Monster
{
public:

    Troll(int playerLevel);

    virtual void generateStats(int playerLevel) override;
};

// 슬라임 클래스
class Slime : public Monster 
{
public:
    Slime(int playerLevel);

    virtual void generateStats(int playerLevel) override;
};

/*****************
    BossMonster
/*****************/

// 추상 클래스(Monster에서 필수 인터페이스 상속 받음)
class BossMonster : public Monster
{
public:
    BossMonster(const string& bossName, int playerLevel);

    // 보스 몬스터 생성 팩토리 메서드
    static unique_ptr<BossMonster> createBossMonster(int playerLevel);
};

// Dragon 클래스 (BossMonster 상속)
class Dragon : public BossMonster
{
public:
    Dragon(int playerLevel);

    virtual void generateStats(int playerLevel) override;
};