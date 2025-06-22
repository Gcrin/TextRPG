#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <memory>

#include "Item.h"

using namespace std;

class Item;

class Character {
private:
    string name;
    int level = 1;
    int health = 200;
    int maxHealth = 200;
    int attack = 30;
    int experience = 0;
    int gold = 0;
    vector<unique_ptr<Item>> inventory;

public:
    Character(const string& name);

    string getName() const;

    int getLevel() const;
    int getHealth() const;
    int getAttack() const;
    int getGold() const;
    int getInventorySize() const;
    int getExperience() const { return experience; }

    void heal(int amount);
    void increaseAttack(int amount);
    void takeDamage(int damage);
    void gainExperience(int exp);
    void gainGold(int amount);
    void addItem(unique_ptr<Item> item);
    void useRandomItem();
    void displayStatus() const;
    void showInventory() const;

    bool isAlive() const;
    bool sellItem(int index, int& goldEarned);
    
    friend class HealthPotion;
    friend class AttackBoost;
};

#endif