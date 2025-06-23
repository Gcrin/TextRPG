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
	std::cout << "-----��ǰ ���-----\n";
	for (int i = 0; i < AvailableItems.size(); i++)
	{
		const auto& item = AvailableItems[i];
		std::cout << "��ǰ��ȣ : " << i << ", ��ǰ�� : " << item->GetName()
			<< ", ���� : " << item->GetPrice() << '\n';
	}
}

void Shop::BuyItem(int index, Character* player)
{
	if (index < 0 || index >= AvailableItems.size())
	{
		std::cout << "�߸��� ��ǰ ��ȣ�Դϴ�.\n";
		return;
	}

	const auto& itemToBuy = AvailableItems[index];

	if (player->GetGold() < itemToBuy->GetPrice())
	{
		std::cout << "�������� �����մϴ�.\n";
		return;
	}
	
	if (player->SpendGold(itemToBuy->GetPrice()))
	{
		std::cout << itemToBuy->GetName() << "�� ���� �߽��ϴ�.\n";
		player->AddItem(itemToBuy->Clone());
	}
}

void Shop::SellItem(int index, Character* player)
{
	const auto& inventory = player->GetInventory();

	if (index < 0 || index >= inventory.size())
	{
		std::cout << "�߸��� ������ ��ȣ�Դϴ�.\n";
		return;
	}

	const auto& itemToSell = inventory[index];
	int sellPrice = itemToSell->GetPrice() * 0.6;

	std::cout << itemToSell->GetName() << "�� " << sellPrice << "��忡 �Ǹ��߽��ϴ�.\n";
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

