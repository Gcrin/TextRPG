#include "Shop.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "Character.h"
#include <iostream>
#include <utility>

Shop::Shop()
{
	AddItem(std::make_unique<HealthPotion>());
	AddItem(std::make_unique<AttackBoost>());
}

Shop::~Shop()
{
}

void Shop::DisplayItems() const
{
	std::cout << "-----상품 목록-----\n";

	if (AvailableItems.empty())
	{
		"판매하는 상품이 없습니다.\n";
		return;
	}

	for (int i = 0; i < AvailableItems.size(); i++)
	{
		const std::unique_ptr<Item>& item = AvailableItems[i];
		std::cout << "상품번호 : " << i << ", 상품명 : " << item->GetName()
			<< ", 가격 : " << item->GetPrice() << '\n';
	}
}

void Shop::BuyItem(int index, Character* player)
{
	if (index < 0 || index >= AvailableItems.size())
	{
		std::cout << "잘못된 상품 번호입니다.\n";
		return;
	}

	const auto& itemToBuy = AvailableItems[index];

	if (player->GetGold() < itemToBuy->GetPrice())
	{
		std::cout << "소지금이 부족합니다.\n";
		return;
	}
	
	if (player->SpendGold(itemToBuy->GetPrice()))
	{
		std::cout << itemToBuy->GetName() << "을 구매 했습니다.\n";
		player->AddItem(itemToBuy->Clone());
	}
}

void Shop::SellItem(int index, Character* player)
{
	const std::vector<std::unique_ptr<Item>>& inventory = player->GetInventory();

	if (index < 0 || index >= inventory.size())
	{
		std::cout << "잘못된 아이템 번호입니다.\n";
		return;
	}

	const auto& itemToSell = inventory[index];
	int sellPrice = itemToSell->GetPrice() * 0.6;

	std::cout << itemToSell->GetName() << "을 " << sellPrice << "골드에 판매했습니다.\n";
	player->AddGold(sellPrice);
	player->RemoveItem(index);
}

void Shop::AddItem(std::unique_ptr<Item> item)
{
	if (item)
	{
		AvailableItems.push_back(std::move(item));
	}
}

