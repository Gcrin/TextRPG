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
	std::cout << "당신의 이름을 알려주세요 : ";
	std::cin >> playerName;

	Character& player = Character::GetInstance(playerName);
	std::cout << player.GetName() << "님, 환영합니다!\n";
	player.DisplayStatus();

	MainLoop(&player);

	std::cout<< "\n게임 종료\n";
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

		std::cout << "\n----- 무엇을 할까? -----\n";
		std::cout << "1. 전투 \n";
		std::cout << "2. 상점 방문\n";
		std::cout << "3. 캐릭터 상태 확인\n";
		std::cout << "4. 전투 기록 보기\n";
		std::cout << "5. 게임 종료\n";
		std::cout << "------------------\n";
		std::cout << "선택 : ";

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
			std::cout << "토벌한 몬스터 수 : " << monstersKillCount << '\n';
			break;
		case 5:
			isGameRunning = false;
			break;
		default:
			std::cout << "잘못된 입력입니다.\n";
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
		std::cout << "몬스터가 나타나지 않았다.\n";
		return;
	}

	std::cout << "\n==============================================\n";
	std::cout << monster->GetName() << "(체력 : " << monster->GetHealth() << ", 공격력 : " << monster->GetAttack() << "와 전투를 시작합니다!\n";
	std::cout << "==============================================\n";

	int turn = 1;
	while (player->GetHealth() > 0 && monster->GetHealth() > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << "\n-----[ " << turn << "번째 턴 ] -----\n";
		
		bool useItem = false;

		// 최대 체력의 30% 이하로 체력이 떨어지면 포션 사용
		if (player->GetHealth() <= player->GetMaxHealth() * 0.3)
		{
			
		}
		
		int playerDamage = player->GetAttack();
		std::cout << player->GetName() << "의 공격! " << monster->GetName() << "에게 " << playerDamage <<"의 데미지를 입혔다!\n";
		monster->TakeDamage(playerDamage);

		if (monster->GetHealth() <=0)
		{
			std::cout << monster->GetName() << "의 남은 체력 : 0\n";
			break;
		}
		std::cout << monster->GetName() << "의 남은 체력 : " << monster->GetHealth() <<'\n';

		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		int monsterDamage = monster->GetAttack();
		std::cout << monster->GetName() << "의 공격! " << player->GetName() << "로부터 " << monsterDamage << "의 데미지를 입었다!\n";
		player->TakeDamage(monsterDamage);

		if (player->GetHealth() <=0)
		{
			std::cout << player->GetName() << "의 남은 체력 : 0\n";
			break;
		}
		std::cout << player->GetName() << "의 남은 체력 : " << player->GetHealth() <<'\n';
	}

	std::cout <<"==============================================\n";

	/*if (player->GetHealth() > 0)
	{
		std::cout << "\n 전투 승리!\n";
		int exp = monster->get
	}*/
}

void GameManager::BossBattle(Character* player)
{

}

void GameManager::VisitShop(Character* player)
{
	std::cout << "\n=====상점에 오신 것을 환영합니다!=====\n";

	while (true)
	{
		std::cout << "\n-----상점 메뉴-----\n";
		std::cout << "소지금 : " << player->GetGold() << "G\n";
		std::cout << "1. 아이템 구매\n";
		std::cout << "2. 아이템 판매\n";
		std::cout << "3. 상점 나가기\n";
		std::cout << "---------------\n";
		std::cout << "원하는 행동을 선택해주세요 : ";
		
		int menuChoice;
		std::cin >> menuChoice;

		if (menuChoice == 1)
		{
			shop->DisplayItems();
			std::cout << "구매할 아이템 번호를 입력하세요 (뒤로가기 : -1) : ";
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
				std::cout << "인벤토리가 비어있습니다.\n";
				continue;
			}
			player->DisplayInventory();
			std::cout << "판매할 아이템 번호를 입력하세요 (뒤로가기 : -1) ";
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
			std::cout << "다음 방문을 기다리겠습니다.\n";
			break;
		}
		else
		{
			std::cout << "잘못된 입력입니다. 다시 선택해주세요.\n";
		}
	}
}

