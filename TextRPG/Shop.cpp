#include "Shop.h"
#include "AttackBoost.h"
#include "Character.h"
#include "HealthPotion.h"

#include <iostream>


Shop::Shop()
{
    items.push_back(std::make_unique<HealthPotion>());
    items.push_back(std::make_unique<AttackBoost>());
}

void Shop::displayShop(Character& character) const
{
    std::cout << "\n==================== ���� ====================\n";
    std::cout << "�������! ������ ���͵帱���?\n";
    std::cout << "���� ���: " << character.getGold() << " Gold\n\n";

    std::cout << "--- �Ǹ� ������ ---\n";
    for (size_t i = 0; i < items.size(); ++i)
    {
        std::cout << i + 1 << ". " << items[i]->getName()
            << " (" << items[i]->getPrice() << " Gold)\n";
    }
    std::cout << "\n";
}

void Shop::buyItem(int itemIndex, Character& character)
{
    if (itemIndex < 1 || itemIndex > items.size())
    {
        std::cout << "�߸��� ��ȣ�Դϴ�.\n";
        return;
    }

    const std::unique_ptr<Item>& item = items[itemIndex - 1];
    if (character.getGold() >= item->getPrice())
    {
        character.removeGold(item->getPrice());
        character.addItem(item->clone());
        std::cout << item->getName() << " ��(��) �����߽��ϴ�!\n";
    }
    else
    {
        std::cout << "��尡 �����մϴ�.\n";
    }
}

void Shop::sellItem(int itemIndex, Character& character)
{
    const auto& inventory = character.getInventory();
    if (itemIndex < 1 || itemIndex > inventory.size())
    {
        std::cout << "�߸��� ��ȣ�Դϴ�.\n";
        return;
    }

    character.sellItem(itemIndex - 1, *this);
}

size_t Shop::getItemCount() const
{
    return items.size();
}