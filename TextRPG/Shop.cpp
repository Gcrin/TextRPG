#include "Shop.h"
#include <iostream>

#include "AttackBoost.h"
#include "Character.h"
#include "HealthPotion.h"

Shop::Shop()
{
    items.push_back(std::make_unique<HealthPotion>());
    items.push_back(std::make_unique<AttackBoost>());
}

void Shop::displayShop(Character& character) const
{
    std::cout << "\n==================== 상점 ====================\n";
    std::cout << "어서오세요! 무엇을 도와드릴까요?\n";
    std::cout << "보유 골드: " << character.getGold() << " Gold\n\n";
}

void Shop::buyItem(int itemIndex, Character& character)
{
    displayShopItems();
    if (itemIndex < 1 || itemIndex > items.size())
    {
        std::cout << "잘못된 번호입니다.\n";
        return;
    }

    const std::unique_ptr<Item>& item = items[itemIndex - 1];
    if (character.getGold() >= item->getPrice())
    {
        character.removeGold(item->getPrice());
        character.addItem(item->clone());
        std::cout << item->getName() << " 을(를) 구매했습니다!\n";
    }
    else
    {
        std::cout << "골드가 부족합니다.\n";
    }
}

void Shop::sellItem(int itemIndex, Character& character)
{
    const auto& inventory = character.getInventory();
    if (itemIndex < 1 || itemIndex > inventory.size())
    {
        std::cout << "잘못된 번호입니다.\n";
        return;
    }

    character.sellItem(itemIndex - 1, *this);
}

size_t Shop::getItemCount() const
{
    return items.size();
}

void Shop::displayShopItems() const
{
    std::cout << "--- 판매 아이템 ---\n";
    for (size_t i = 0; i < items.size(); ++i)
    {
        std::cout << i + 1 << ". " << items[i]->getName()
            << " (" << items[i]->getPrice() << " Gold)\n";
    }
    std::cout << "\n";
}