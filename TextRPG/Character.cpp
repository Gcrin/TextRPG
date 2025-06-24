#include "Character.h"
#include "Item.h"
#include <iostream>
#include <algorithm>

Character::Character(std::string name)
	: Name(name), Level(1),
	  Health(200), MaxHealth(200),
	  Attack(30), Experience(0), Gold(0) 
{
	std::cout << "ĳ���� " << Name << "���� �Ϸ�!\n";
}

Character::~Character()
{
}

Character& Character::GetInstance(const std::string& name)
{
	static Character Instance(name);
	return Instance;
}

void Character::DisplayStatus() const
{
	std::cout << "===================================\n";
	std::cout << "���� : " << Level << ", ü�� : " << Health << ", ���ݷ� : " << Attack << '\n';
	std::cout << "===================================\n";
	std::cout << "������ : " << Gold << "G, ����ġ : " << Experience << "/100\n";
	std::cout << "===================================\n";
}

void Character::GainExperience(int amount)
{
	if (Level >= 10) return;

	std::cout << "����ġ " << amount << "�� ȹ���ߴ�!\n";
	Experience += amount;

	while (Level < 10 && Experience >= 100)
	{
		LevelUp();
	}
}

void Character::LevelUp()
{
	Level++;
	Experience -= 100;
	MaxHealth += 20;
	Health = MaxHealth;
	Attack += 5;

	std::cout << "\n***** LEVEL UP! *****\n";
	std::cout << "���� " << Level << "�޼�!\n";
}

void Character::AddItem(std::unique_ptr<Item> item)
{
	if (item == nullptr) return;

	Inventory.push_back(std::move(item));
}

void Character::UseItem(int index)
{
	if (index < 0 && index >= Inventory.size())
	{
		std::cout << "�������� �������� �ʽ��ϴ�.\n";
		return;
	}

	Inventory[index]->Use(this);
	RemoveItem(index);
}

void Character::RemoveItem(int index)
{
	if (index < 0 || index >= Inventory.size())
	{
		return;
	}

	Inventory.erase(Inventory.begin() + index);
}

void Character::DisplayInventory() const
{
	std::cout << "\n===== �κ��丮 =====\n";
	if (Inventory.empty())
	{
		std::cout << "����ֽ��ϴ�.\n";
	}

	for (int i=0; i<Inventory.size(); i++)
	{
		std::cout << "������" << i << " : " << Inventory[i]->GetName() << '\n';
	}
	std::cout << "====================\n";
}

int Character::FindItemIndex(ItemID id)
{
	for (int i = 0; i < Inventory.size(); i++)
	{
		if (Inventory[i] && Inventory[i]->GetId() == id)
		{
			return i;
		}
	}
	return -1;
}

void Character::AddGold(int amount)
{
	std::cout << "��� " << amount << "G�� ȹ���ߴ�!\n";
	Gold += amount;
}

bool Character::SpendGold(int amount)
{
	if (Gold < amount)
	{
		return false;
	}
	
	Gold -= amount;
	return true;
}


void Character::IncreaseAttack(int amount)
{
	std::cout << "���ݷ� ����!\n";
	Attack += amount;
	std::cout << "���� ���ݷ� : " << GetAttack() << '\n';
}

void Character::RestoreHealth(int amount)
{
	std::cout << "ü�� ȸ��!\n";
	Health += amount;
	Health = std::min(Health, MaxHealth);
	std::cout << "���� ü�� : " << GetHealth() << '\n';
}

void Character::TakeDamage(int damage)
{
	Health -= damage;
	Health = std::max(Health, 0);
}

const std::vector<std::unique_ptr<Item>>& Character::GetInventory() const
{
	return Inventory;
}
