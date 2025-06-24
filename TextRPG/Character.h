#pragma once
#include "Item.h"
#include "Shop.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Character
{
public:
    Character(std::string name);

    void displayStatus() const;

    int getLevel() const { return level; }
    int getAttack() const { return attack; }
    int getHealth() const { return currentHealth; }
    int getGold() const { return gold; }
    int getExperience() const { return experience; }
    std::string getName() const { return name; }
    const std::vector<std::unique_ptr<Item>>& getInventory() const { return inventory; }

    // 전투 관련
    void increaseAttack(int amount) { attack += amount; }
    void heal(int amount);
    void takeDamage(int damage);
    void addExperience(int exp);

    // 아이템 관련
    void displayInventory() const;
    bool hasItem() const { return !inventory.empty(); }
    void useItem(int index);
    void addItem(std::unique_ptr<Item> item);
    void sellItem(int index, Shop& shop);
    void addGold(int amount) { gold += amount; }
    void removeGold(int amount) { gold -= amount; }

private:
    std::string name;
    int level;
    int maxHealth;
    int currentHealth;
    int attack;
    int experience;
    int gold;
    std::vector<std::unique_ptr<Item>> inventory;

    void levelUp();
};