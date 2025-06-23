#pragma once
#include <string>
#include <vector>
#include "Item.h"

class Character {
private:
    static Character* instance;
    Character(const std::string& name);

    std::string name;
    int level, health, maxHealth, attack, experience, gold;
    std::vector<Item*> inventory;

public:
    static Character* getInstance(const std::string& name = "");

    void displayStatus() const;
    void levelUp();
    void takeDamage(int damage);
    void addExperience(int exp);
    void addGold(int amount);
    void useItem(int index);
    void addItem(Item* item);
    bool isAlive() const;

    // 상점 기능
    void visitShop();

    // Getter
    std::string getName() const;
    int getLevel() const;
    int getAttack() const;
    int getHealth() const;
    int getGold() const;
    std::vector<Item*>& getInventory();
};
