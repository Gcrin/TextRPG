#include "Character.h"
#include "Shop.h"

#include <algorithm>
#include <iostream>

Character::Character(std::string name) : name(std::move(name)), level(1), maxHealth(200), currentHealth(maxHealth),
attack(30), experience(0), gold(0)
{
}

void Character::displayStatus() const
{
    std::cout << "레벨: " << level << ", 체력: " << currentHealth << ", 공격력: " << attack << "\n";
}

void Character::heal(int amount)
{
    currentHealth += amount;
    currentHealth = std::min(currentHealth, maxHealth);
}

void Character::takeDamage(int damage)
{
    currentHealth -= damage;
    currentHealth = std::max(currentHealth, 0);
}

void Character::addExperience(int exp)
{
    experience += exp;
    std::cout << name << "이(가) " << exp << "의 경험치를 획득했습니다. (현재 경험치: " << experience << "/100)\n";
    if (experience >= 100)
    {
        levelUp();
    }
}

void Character::displayInventory() const
{
    std::cout << "\n--- 인벤토리 ---\n";
    if (inventory.empty())
    {
        std::cout << "비어있음\n";
    }
    else
    {
        for (size_t i = 0; i < inventory.size(); ++i)
        {
            std::cout << i + 1 << ". " << inventory[i]->getName() << "\n";
        }
    }
    std::cout << "----------------\n";
}

void Character::useItem(int index)
{
    if (index >= 0 && index < inventory.size())
    {
        inventory[index]->use(*this);
        inventory.erase(inventory.begin() + index);
    }
}

void Character::addItem(std::unique_ptr<Item> item)
{
    inventory.push_back(std::move(item));
}

void Character::sellItem(int index, Shop& shop)
{
    if (index >= 0 && index < inventory.size())
    {
        int sellPrice = static_cast<int>(inventory[index]->getPrice() * 0.6);
        std::cout << inventory[index]->getName() << " 을(를) " << sellPrice << " Gold에 판매했습니다.\n";
        addGold(sellPrice);
        inventory.erase(inventory.begin() + index);
    }
}

void Character::levelUp()
{
    if (level >= 10) return;

    while (experience >= 100)
    {
        if (level >= 10) break;
        level++;
        experience -= 100;
        maxHealth += level * 20;
        attack += level * 5;
        currentHealth = maxHealth;
        std::cout << "\n*** 레벨업! ***\n"
            << name << "이(가) 레벨 " << level << "이(가) 되었습니다!\n"
            << "최대 체력과 공격력이 상승하고, 체력이 모두 회복되었습니다.\n";
    }
    displayStatus();
}