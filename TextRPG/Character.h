#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Item.h"
#include "Shop.h"

class Character
{
public:
    Character(std::string name);

    void displayStatus() const;
    void takeDamage(int damage);
    void addExperience(int exp);
    void addItem(std::unique_ptr<Item> item);
    void useItem(int index);
    void sellItem(int index, Shop& shop);

    void displayInventory() const;

    bool hasItem() const { return !inventory.empty(); }
    int getLevel() const { return level; }
    int getAttack() const { return attack; }
    int getHealth() const { return currentHealth; }
    int getGold() const { return gold; }
    int getExperience() const { return experience; }
    std::string getName() const { return name; }
    const std::vector<std::unique_ptr<Item>>& getInventory() const { return inventory; }

    void addGold(int amount) { gold += amount; }
    void removeGold(int amount) { gold -= amount; }
    void increaseAttack(int amount) { attack += amount; }
    void heal(int amount);

private:
    void levelUp();

    std::string name;
    int level;
    int maxHealth;
    int currentHealth;
    int attack;
    int experience;
    int gold;
    std::vector<std::unique_ptr<Item>> inventory;
};
