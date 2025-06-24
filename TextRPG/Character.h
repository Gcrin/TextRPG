#pragma once
#include "Enums.h"
#include <string>
#include <vector>
#include <memory>

class Item;

class Character
{
private:
    std::string Name;
    int Level;
    int Health;
    int MaxHealth;
    int Attack;
    int Experience;
    int Gold;
    std::vector<std::unique_ptr<Item>> Inventory;

    Character(std::string name);

    void LevelUp();
    
public:
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;
    ~Character();

    static Character& GetInstance(const std::string& name = "");

    void DisplayStatus() const;
    
    void GainExperience(int amount);
    
    void AddItem(std::unique_ptr<Item> item);
    void UseItem(int index);
    void RemoveItem(int index);
    void DisplayInventory() const;
    int FindItemIndex(ItemID id);

    void AddGold(int amount);
    bool SpendGold(int amount);

    void IncreaseAttack(int amount);
    void RestoreHealth(int amount);
    void TakeDamage(int damage);

    const std::vector<std::unique_ptr<Item>>& GetInventory() const;

    std::string GetName() const { return Name; }
    int GetLevel() const { return Level; }
    int GetHealth() const { return Health; }
    int GetMaxHealth() const { return MaxHealth;}
    int GetAttack() const { return Attack; }
    int GetGold() const { return Gold; }
    int GetExperience() const { return Experience; }
    
};
