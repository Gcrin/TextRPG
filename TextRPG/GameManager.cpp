#include "GameManager.h"
#include <iostream>

void GameManager::Run()
{
    CreatePlayer();
    while (!isGameOver)
    {
        StartBattle();
    }
}

void GameManager::CreatePlayer()
{
    std::cout << "캐릭터 이름을 입력하세요: ";
    std::string name;
    std::getline(std::cin, name);
    system("cls");
    player = std::make_unique<Character>(name);
    std::cout << "캐릭터 " << name << " 생성 완료!";
    player->displayStatus();
}


void GameManager::StartBattle()
{
    auto monster = CreateMonster();
    std::cout << "몬스터 " << monster->getName() << " 등장! " << "체력: " << monster->getHealth() << ", 공격력: " << monster->getAttack() << "\n\n";

    //전투 부분
    while (player->getHealth() > 0 && !monster->isDead())
    {

        if (Utils::getRandomInt(1, 10) <= 2) // 20% 확률로 아이템 사용
        {
            if (player->hasItem())
            {
                int itemChoice = Utils::getRandomInt(0, player->getInventory().size());
                player->useItem(itemChoice);
            }
        }

        // 플레이어 공격
        int playerAttack = player->getAttack();
        monster->takeDamage(playerAttack);
        std::cout << player->getName() << "이(가) " << monster->getName() << "을(를) 공격합니다! "
            << monster->getName() << " 체력: " << monster->getHealth() << "\n";

        if (monster->isDead()) break;

        // 몬스터 공격
        int monsterAttack = monster->getAttack();
        int playerHealthBefore = player->getHealth();
        player->takeDamage(monsterAttack);
        std::cout << monster->getName() << "이(가) " << player->getName() << "을(를) 공격합니다! "
            << player->getName() << " 체력: " << playerHealthBefore << " -> " << player->getHealth() << "\n";
    }

    //전투 종료

    if (monster->isDead())
    {
        std::cout << "\n*** " << monster->getName() << " 처치! 전투에서 승리했습니다! ***\n";

        if (dynamic_cast<BossMonster*>(monster.get()))
        {
            std::cout << "보스 " << monster->getName() << "을(를) 처치하고 게임을 클리어했습니다!\n";
            isGameOver = true;
            return;
        }

        int goldAmount = Utils::getRandomInt(10, 20);
        player->addGold(goldAmount);
        player->addExperience(50);

        std::cout << "Hero가 50 EXP와 " << goldAmount << " 골드를 획득했습니다. "
            << "현재 EXP: " << player->getExperience() << "/100, 골드: " << player->getGold() << "\n";

        auto droppedItem = monster->dropItem();
        if (droppedItem)
        {
            std::cout << "[아이템]" << droppedItem->getName() << "을(를) 획득했습니다!\n";
            player->addItem(std::move(droppedItem));
        }

        visitShop();
    }
    else
    {
        std::cout << "\n*** " << player->getName() << "이(가) 사망했습니다. 게임 오버! ***\n";
        isGameOver = true;
    }
}

std::unique_ptr<Monster> GameManager::CreateMonster()
{
    int level = player->getLevel();
    if (level >= 10)
    {
        return std::make_unique<BossMonster>(level);
    }
    int monsterType = Utils::getRandomInt(1, 4);
    switch (monsterType)
    {
    case 1:
        return std::make_unique<Goblin>(level);
    case 2:
        return std::make_unique<Orc>(level);
    case 3:
        return std::make_unique<Troll>(level);
    case 4:
        return std::make_unique<Slime>(level);
    default:
        return std::make_unique<Goblin>(level);
    }
}

void GameManager::visitShop()
{
    std::cout << "\n상점을 방문하시겠습니까? (Y/N): ";
    if (!getInputYesNo())
    {
        std::cout << "모험을 계속합니다.\n";
        return;
    }
    Shop shop;

    while (true)
    {
        shop.displayShop(*player);
        std::cout << "\n무엇을 하시겠습니까?\n"
            << "1. 아이템 구매\n"
            << "2. 아이템 판매\n"
            << "3. 상점 나가기\n"
            << "선택: ";

        int input = getInputRangeInt(1, 3);

        if (input == 1)
        {
            std::cout << "구매할 아이템 번호를 선택하세요 (취소: 0): ";
            int buyInput = getInputRangeInt(0, shop.getItemCount());
            if (buyInput > 0)
            {
                shop.buyItem(buyInput, *player);
            }
        }
        else if (input == 2)
        {
            if (!player->hasItem())
            {
                std::cout << "판매할 아이템이 없습니다.\n";
            }
            else
            {
                player->displayInventory();
                std::cout << "판매할 아이템 번호를 입력하세요 (취소: 0): ";
                int sellInput = getInputRangeInt(0, player->getInventory().size());
                if (sellInput > 0)
                {
                    shop.sellItem(sellInput, *player);
                }
            }
        }
        else if (input == 3)
        {
            std::cout << "상점에서 나왔습니다.\n";
            break;
        }
    }
}

bool GameManager::getInputYesNo() const
{
    char c;
    while (true)
    {
        std::cin >> c;
        system("cls");
        c = std::tolower(c);
        if (c == 'y' || c == 'n')
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return (c == 'y');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "잘못된 입력입니다. Y 또는 N을 입력해주세요: ";
    }
}

int GameManager::getInputRangeInt(int min, int max) const
{
    int input;
    while (true)
    {
        std::cout << "선택: ";
        std::cin >> input;
        system("cls");
        if (std::cin.good() && input >= min && input <= max)
        {
            // 버퍼에 남아있는 모든 내용물(잘못된 입력 + 엔터키)을 다음 줄바꿈 문자('\n')까지 확실하게 비운다.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "잘못된 입력입니다. " << min << "에서 " << max << " 사이의 숫자를 입력해주세요.\n";
    }
}