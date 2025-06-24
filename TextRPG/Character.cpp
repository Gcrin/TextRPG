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
    std::cout << "����: " << level << ", ü��: " << currentHealth << ", ���ݷ�: " << attack << "\n";
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
    std::cout << name << "��(��) " << exp << "�� ����ġ�� ȹ���߽��ϴ�. (���� ����ġ: " << experience << "/100)\n";
    if (experience >= 100)
    {
        levelUp();
    }
}

void Character::displayInventory() const
{
    std::cout << "\n--- �κ��丮 ---\n";
    if (inventory.empty())
    {
        std::cout << "�������\n";
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
        std::cout << inventory[index]->getName() << " ��(��) " << sellPrice << " Gold�� �Ǹ��߽��ϴ�.\n";
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
        std::cout << "\n*** ������! ***\n"
            << name << "��(��) ���� " << level << "��(��) �Ǿ����ϴ�!\n"
            << "�ִ� ü�°� ���ݷ��� ����ϰ�, ü���� ��� ȸ���Ǿ����ϴ�.\n";
    }
    displayStatus();
}