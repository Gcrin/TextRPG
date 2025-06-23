#include "GameManager.h"
#include "Character.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "BossMonster.h"
#include "Shop.h"
#include <iostream>
#include <thread>
#include <chrono>

GameManager::GameManager() : shop(std::make_unique<Shop>()), randomEngine(std::random_device{}()), monstersKillCount(0)
{
}

void GameManager::Run()
{
	std::string playerName;
	std::cout << "����� �̸��� �˷��ּ��� : ";
	std::cin >> playerName;

	Character& player = Character::GetInstance(playerName);
	std::cout << player.GetName() << "��, ȯ���մϴ�!\n";
	player.DisplayStatus();

	MainLoop(&player);

	std::cout<< "\n���� ����\n";
}

void GameManager::MainLoop(Character* player)
{
	bool isGameRunning = true;
	while (isGameRunning)
	{
		if (player->GetLevel() >= 10)
		{
			BossBattle(player);
			isGameRunning = false;
			continue;
		}

		std::cout << "\n----- ������ �ұ�? -----\n";
		std::cout << "1. ���� \n";
		std::cout << "2. ���� �湮\n";
		std::cout << "3. ĳ���� ���� Ȯ��\n";
		std::cout << "4. ���� ��� ����\n";
		std::cout << "5. ���� ����\n";
		std::cout << "------------------\n";
		std::cout << "���� : ";

		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			Battle(player);
			break;
		case 2:
			VisitShop(player);
			break;
		case 3:
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
		
	}
}

std::unique_ptr<Monster> GameManager::GenerateMonster(int level)
{
	std::uniform_int_distribution<int> dis(0, 2);
	
	switch (dis(randomEngine))
	{
	case 0: 
		return std::make_unique<Goblin>(level, randomEngine);
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
	auto monster = GenerateMonster(player->GetLevel());
	if (!monster)
	{
		std::cout << "���Ͱ� ��Ÿ���� �ʾҴ�.\n";
		return;
	}

	std::cout << "\n==============================================\n";
	std::cout << monster->GetName() << "(ü�� : " << monster->GetHealth() << ", ���ݷ� : " << monster->GetAttack() << "�� ������ �����մϴ�!\n";
	std::cout << "==============================================\n";

	int turn = 1;
	while (player->GetHealth() > 0 && monster->GetHealth() > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << "\n-----[ " << turn << "��° �� ] -----\n";
		
		bool useItem = false;

		// �ִ� ü���� 30% ���Ϸ� ü���� �������� ���� ���
		if (player->GetHealth() <= player->GetMaxHealth() * 0.3)
		{
			
		}
		
		int playerDamage = player->GetAttack();
		std::cout << player->GetName() << "�� ����! " << monster->GetName() << "���� " << playerDamage <<"�� �������� ������!\n";
		monster->TakeDamage(playerDamage);

		if (monster->GetHealth() <=0)
		{
			std::cout << monster->GetName() << "�� ���� ü�� : 0\n";
			break;
		}
		std::cout << monster->GetName() << "�� ���� ü�� : " << monster->GetHealth() <<'\n';

		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		int monsterDamage = monster->GetAttack();
		std::cout << monster->GetName() << "�� ����! " << player->GetName() << "�κ��� " << monsterDamage << "�� �������� �Ծ���!\n";
		player->TakeDamage(monsterDamage);

		if (player->GetHealth() <=0)
		{
			std::cout << player->GetName() << "�� ���� ü�� : 0\n";
			break;
		}
		std::cout << player->GetName() << "�� ���� ü�� : " << player->GetHealth() <<'\n';
	}

	std::cout <<"==============================================\n";

	/*if (player->GetHealth() > 0)
	{
		std::cout << "\n ���� �¸�!\n";
		int exp = monster->get
	}*/
}

void GameManager::BossBattle(Character* player)
{

}

void GameManager::VisitShop(Character* player)
{
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

