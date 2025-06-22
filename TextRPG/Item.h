#pragma once

#include <string>
#include <memory>
using namespace std;

class Character;

class Item 
{
public:
    // 생성자
    Item(const string& itemName) : name(itemName) {}

    virtual ~Item() = default;

    // 아이템 인터페이스
    virtual void use(Character* character) = 0;

    // Getter
    string getName() const { return name; }

    // 랜덤 아이템 생성 함수
    static unique_ptr<Item> createRandomItem();

protected:
    string name;
};

class HealthPotion : public Item 
{
public:

    HealthPotion() : Item("HealthPotion"), healthRestore(50) {}

    virtual void use(Character* character) override;

    // Getter
    int getHealthRestore() const { return healthRestore; }

private:
    int healthRestore;
};

class AttackBoost : public Item 
{
public:

    AttackBoost() : Item("AttackBoost"), attackIncrease(10) {}

    virtual void use(Character* character) override;

    // Getter
    int getAttackIncrease() const { return attackIncrease; }

private:
    int attackIncrease;
};
