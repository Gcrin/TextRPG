#include "GameManager.h"
#include "Character.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "BossMonster.h"
#include "Shop.h"
#include "Util.h"
#include "Item.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>

GameManager::GameManager() : shop(std::make_unique<Shop>()), monstersKillCount(0), isGameRunning(true)
{
}

GameManager::~GameManager()
{
}

void GameManager::Run()
{
	std::string playerName;
	std::cout << "����� �̸��� �˷��ּ��� : ";
	std::getline(std::cin, playerName);

	if (playerName.empty())
	{
		playerName = "Guest";
	}

	Character& player = Character::GetInstance(playerName);
	std::cout << player.GetName() << "��, ȯ���մϴ�!\n";
	player.DisplayStatus();

	MainLoop(&player);

	std::cout<< "\n���� ����\n";
}

void GameManager::MainLoop(Character* player)
{
	while (isGameRunning)
	{

		std::cout << "\n----- ������ �ұ�? -----\n";
		std::cout << "1. ���� \n";
		std::cout << "2. ���� �湮\n";
		std::cout << "3. ĳ���� ���� Ȯ��\n";
		std::cout << "4. ���� ��� ����\n";
		std::cout << "5. ���� ����\n";
		std::cout << "------------------------\n";
		std::cout << "���� : ";

		int choice;
		std::cin >> choice;

		if (std::cin.fail())
		{
			std::cout << "�߸��� �Է��Դϴ�. ���ڸ� �Է����ּ���.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}


		switch (choice)
		{
		case 1:
			Battle(player);
			player->DisplayStatus();
			break;
		case 2:
			VisitShop(player);
			break;
		case 3:
			ClearConsole();
			player->DisplayStatus();
			player->DisplayInventory();
			break;
		case 4:
			std::cout << "����� ���� �� : " << monstersKillCount << '\n';
			break;
		case 5:
			isGameRunning = false;
			break;
		default:
			std::cout << "�߸��� �Է��Դϴ�.\n";
			break;
		}
		
		if (player->GetHealth() <= 0)
		{
			isGameRunning = false;
		}
	}
}

std::unique_ptr<Monster> GameManager::GenerateMonster(int level)
{
	int dis = RandomUtil::GetRandomInt(0, 2);
	switch (dis)
	{
	case 0:
		return std::make_unique<Goblin>(level);
	case 1: 
		return std::make_unique<Orc>(level);
	case 2:
		return std::make_unique<Troll>(level);
	default:
		break;
	}
	return nullptr;
}

std::unique_ptr<BossMonster> GameManager::GenerateBossMonster(int level)
{
	return std::make_unique<BossMonster>(level);
}



void GameManager::Battle(Character* player)
{
	if (player->GetLevel() >= 10)
	{
		std::cout << "����� ����� ���������ϴ�. ���� ������ ���� ������ �ð��Դϴ�.\n";
		BossBattle(player);
		std::this_thread::sleep_for(std::chrono::seconds(2));
		isGameRunning = false;
		return;
	}
	ClearConsole();
	std::unique_ptr<Monster> monster = GenerateMonster(player->GetLevel());
	if (!monster)
	{
		std::cout << "���Ͱ� ��Ÿ���� �ʾҴ�.\n";
		return;
	}

	std::cout << "\n================================================\n";
	std::cout << monster->GetName() << "(ü�� : " << monster->GetHealth() << ", ���ݷ� : " << monster->GetAttack() << ")�� ������ �����մϴ�!\n";
	std::cout << "================================================\n";

	TurnBasedCombat(player, monster.get());

	if (player->GetHealth() > 0)
	{
		std::cout << "\n���� �¸�!\n";
		monstersKillCount++;
		
		player->AddGold(monster->GetGold());
		player->GainExperience(monster->GetExperience());
		
		std::unique_ptr<Item> droppedItem = monster->DropItem();
		if (droppedItem)
		{
			player->AddItem(std::move(droppedItem));
		}
	}
	else
	{
		std::cout << "\n �������� �й��߽��ϴ�....\n";
	}
}

void GameManager::BossBattle(Character* player)
{
	ClearConsole();
	std::cout << "\n ===== ������ ������ �ٰ��ɴϴ� =====\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::unique_ptr<Monster> boss = GenerateBossMonster(player->GetLevel());
	if (!boss)
	{
		return;
	}

	std::cout << "\n==============================================\n";
	std::cout << boss->GetName() << "(ü�� : " << boss->GetHealth() << ", ���ݷ� : " << boss->GetAttack() << ")�� ������ �����մϴ�!\n";
	std::cout << "\n==============================================\n";

	TurnBasedCombat(player, boss.get());

	std::cout << "==============================================\n";

	if (player->GetHealth() > 0)
	{
		std::cout << "\n ���� �¸�!\n";
		monstersKillCount++;

		std::cout << "�����մϴ�! ���������� óġ�Ͽ� ������ ���߽��ϴ�!!\n";
		std::cout << "********** GAME CLEAR **********\n";
	}
	else
	{
		std::cout << "\n ������������ �й��߽��ϴ�....\n";
		std::cout << "********** GAME OVER **********\n";
	}
}

bool GameManager::AutoItemUse(Character* player)
{
	if (player->GetInventory().empty())
	{
		return false;
	}

	// �ִ� ü���� 30% ���Ϸ� ü���� �������� ���� ���
	if (player->GetHealth() <= player->GetMaxHealth() * 0.3)
	{
		int potionIndex = player->FindItemIndex(ItemID::HealthPotion);
		if (potionIndex != -1)
		{
			std::cout << player->GetName() << "�� ������ ����մϴ�!\n";
			player->UseItem(potionIndex);
			return true;
		}
	}

	// ���� ���۽� AttackBoost ������ �����ϸ� ���
	int boostIndex = player->FindItemIndex(ItemID::AttackBoost);
	if (boostIndex != -1)
	{
		std::cout << player->GetName() << "�� ���ݷ� �ν�Ʈ�� ����մϴ�!\n";
		player->UseItem(boostIndex);
		return true;
	}
	
	return false;
}

void GameManager::TurnBasedCombat(Character* player, Monster* monster)
{
	int turn = 1;
	while (player->GetHealth() > 0 && monster->GetHealth() > 0)
	{
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "\n-----[ " << turn << "��° �� ] -----\n";

		bool usedItem = AutoItemUse(player);

		if (!usedItem)
		{
			int playerDamage = player->GetAttack();
			std::cout << player->GetName() << "�� ����! " 
				<< monster->GetName() << "���� " 
				<< playerDamage << "�� �������� ������!\n";
			monster->TakeDamage(playerDamage);
		}

		if (monster->GetHealth() <= 0)
		{
			std::cout << monster->GetName() << "�� ���� ü�� : 0\n";
			break;
		}
		std::cout << monster->GetName() << "�� ���� ü�� : " << monster->GetHealth() << '\n';

		std::this_thread::sleep_for(std::chrono::seconds(2));

		int monsterDamage = monster->GetAttack();
		std::cout << monster->GetName() << "�� ����! " << player->GetName() << "�κ��� " << monsterDamage << "�� �������� �Ծ���!\n";
		player->TakeDamage(monsterDamage);

		if (player->GetHealth() <= 0)
		{
			std::cout << player->GetName() << "�� ���� ü�� : 0\n";
			break;
		}
		std::cout << player->GetName() << "�� ���� ü�� : " << player->GetHealth() << '\n';
		turn++;
	}
}



void GameManager::VisitShop(Character* player)
{
	ClearConsole();
	std::cout << "\n=====������ ���� ���� ȯ���մϴ�!=====\n";

	while (true)
	{
		std::cout << "\n-----���� �޴�-----\n";
		std::cout << "������ : " << player->GetGold() << "G\n";
		std::cout << "1. ������ ����\n";
		std::cout << "2. ������ �Ǹ�\n";
		std::cout << "3. ���� ������\n";
		std::cout << "---------------\n";
		std::cout << "���ϴ� �ൿ�� �������ּ��� : ";
		
		int menuChoice;
		std::cin >> menuChoice;

		if (menuChoice == 1)
		{
			shop->DisplayItems();
			std::cout << "������ ������ ��ȣ�� �Է��ϼ��� (�ڷΰ��� : -1) : ";
			int buyChoice;
			std::cin >> buyChoice;
			if (buyChoice == -1)
			{
				continue;
			}
			shop->BuyItem(buyChoice, player);
		}
		else if (menuChoice == 2)
		{
			if (player->GetInventory().empty())
			{
				std::cout << "�κ��丮�� ����ֽ��ϴ�.\n";
				continue;
			}
			player->DisplayInventory();
			std::cout << "�Ǹ��� ������ ��ȣ�� �Է��ϼ��� (�ڷΰ��� : -1) ";
			int sellChoice;
			std::cin >> sellChoice;
			if (sellChoice == -1)
			{
				continue;
			}
			shop->SellItem(sellChoice, player);

		}
		else if (menuChoice == 3)
		{
			std::cout << "���� �湮�� ��ٸ��ڽ��ϴ�.\n";
			break;
		}
		else
		{
			std::cout << "�߸��� �Է��Դϴ�. �ٽ� �������ּ���.\n";
		}
	}
}

void GameManager::ClearConsole()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}