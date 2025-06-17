#include "Character.h"
#include <algorithm>
#include <iostream>

void Character::displayStatus() const
{
    std::cout << "\n--- 캐릭터 상태 ---\n"
        << "이름: " << name << "\n"
        << "레벨: " << level << " (최대 레벨: 10)\n"
        << "체력: " << currentHealth << " / " << maxHealth << "\n"
        << "공격력: " << attack << "\n"
        << "경험치: " << experience << " / 100\n"
        << "골드: " << gold << " Gold\n"
        << "-------------------\n";
}

void Character::takeDamage(int damage)
{
    currentHealth -= damage;
    currentHealth = std::max(currentHealth, 0);
    std::cout << name << "이(가) " << damage << "의 피해를 입었습니다! 현재 체력: " << currentHealth << "\n";
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

void Character::addItem(std::unique_ptr<Item> item)
{
    inventory.push_back(std::move(item));
}

void Character::useItem(int index)
{
    if (index >= 0 && index < inventory.size())
    {
        inventory[index]->use(*this);
        inventory.erase(inventory.begin() + index);
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

void Character::heal(int amount)
{
    currentHealth += amount;
    currentHealth = std::min(currentHealth, maxHealth);
}

Character::Character(std::string name) : name(std::move(name)), level(1), maxHealth(200), currentHealth(maxHealth),
                                         attack(30), experience(0), gold(0)
{
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
