#include "Monster.h"
#include <iostream>
#include <random>
#include "GameManager.h"

Monster::Monster(const string& monsterName, int monsterLevel)
    : name(monsterName), health(0), attack(0), level(monsterLevel)
{

}

void Monster::takeDamage(int damage) 
{
    health -= damage;
    if (health < 0) health = 0;
}

void Monster::displayInfo() const
{
    cout << "몬스터 " << name << " 등장! "
        << "체력: " << health << ", 공격력: " << attack << endl;
}

// 균등 확률 랜덤 몬스터 생성 
unique_ptr<Monster> Monster::createRandomMonster(int playerLevel)
{
    GameManager* gm = GameManager::getInstance();
    int randomChoice = gm->getRandomInt(0, 3);

    switch (randomChoice) 
    {
    case 0:
        return make_unique<Goblin>(playerLevel);
    case 1:
        return make_unique<Orc>(playerLevel);
    case 2:
        return make_unique<Troll>(playerLevel);
    case 3:
    default:
        return make_unique<Slime>(playerLevel);
    }
}

// Goblin 구현
Goblin::Goblin(int playerLevel) : Monster("고블린", playerLevel) 
{
    generateStats(playerLevel);
}

void Goblin::generateStats(int playerLevel) 
{
    GameManager* gm = GameManager::getInstance();

    // 고블린의 랜덤 스텟
    health = gm->getRandomInt(playerLevel * 20, playerLevel * 30);
    attack = gm->getRandomInt(playerLevel * 5, playerLevel * 10);
}

Orc::Orc(int playerLevel) : Monster("오크", playerLevel) 
{
    generateStats(playerLevel);
}

void Orc::generateStats(int playerLevel) 
{
    GameManager* gm = GameManager::getInstance();

    // 오크의 랜덤 스텟 (체력 +10%, 공격력 +20%)
    int healthMin = static_cast<int>(playerLevel * 20 * 1.1);
    int healthMax = static_cast<int>(playerLevel * 30 * 1.1);
    health = gm->getRandomInt(healthMin, healthMax);

    int attackMin = static_cast<int>(playerLevel * 5 * 1.2);
    int attackMax = static_cast<int>(playerLevel * 10 * 1.2);
    attack = gm->getRandomInt(attackMin, attackMax);
}

Troll::Troll(int playerLevel) : Monster("트롤", playerLevel) 
{
    generateStats(playerLevel);
}

void Troll::generateStats(int playerLevel) 
{
    GameManager* gm = GameManager::getInstance();

    static random_device rd;
    static mt19937 gen(rd());

    // 트롤의 랜덤 스텟 (체력 +30%, 공격력 기본)
    int healthMin = static_cast<int>(playerLevel * 20 * 1.3);
    int healthMax = static_cast<int>(playerLevel * 30 * 1.3);
    health = gm->getRandomInt(healthMin, healthMax);

    attack = gm->getRandomInt(playerLevel * 5, playerLevel * 10);
}

Slime::Slime(int playerLevel) : Monster("슬라임", playerLevel) 
{
    generateStats(playerLevel);
}

void Slime::generateStats(int playerLevel) 
{
    GameManager* gm = GameManager::getInstance();

    // 최약체 슬라임의 스텟 (체력 -20%, 공격력 -10%)
    int healthMin = static_cast<int>(playerLevel * 20 * 0.8);
    int healthMax = static_cast<int>(playerLevel * 30 * 0.8);
    health = gm->getRandomInt(healthMin, healthMax);

    int attackMin = static_cast<int>(playerLevel * 5 * 0.9);
    int attackMax = static_cast<int>(playerLevel * 10 * 0.9);
    attack = gm->getRandomInt(attackMin, attackMax);
}

/*****************
    BossMonster
/*****************/

BossMonster::BossMonster(const string& bossName, int playerLevel)
    : Monster(bossName, playerLevel)
{
}

unique_ptr<BossMonster> BossMonster::createBossMonster(int playerLevel)
{
    // 현재는 Dragon만 있지만 추후 다른 보스 추가 고려 설계
    return make_unique<Dragon>(playerLevel);
}

Dragon::Dragon(int playerLevel) : BossMonster("드래곤", playerLevel)
{
    generateStats(playerLevel);
}

void Dragon::generateStats(int playerLevel)
{
    GameManager* gm = GameManager::getInstance();

    // 기본 몬스터 스탯 계산 (일반 몬스터와 동일한 공식)
    int baseHealthMin = playerLevel * 20;
    int baseHealthMax = playerLevel * 30;
    int baseAttackMin = playerLevel * 5;
    int baseAttackMax = playerLevel * 10;

    // 보스는 기본 스탯의 1.5배로 강화
    int healthMin = static_cast<int>(baseHealthMin * 1.5);
    int healthMax = static_cast<int>(baseHealthMax * 1.5);
    int attackMin = static_cast<int>(baseAttackMin * 1.5);
    int attackMax = static_cast<int>(baseAttackMax * 1.5);

    // 1.5배 범위에서 랜덤 스탯 생성
    health = gm->getRandomInt(healthMin, healthMax);
    attack = gm->getRandomInt(attackMin, attackMax);
}