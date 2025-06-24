#include "GameManager.h"
#include "Utils.h"
#include <iostream>

void GameManager::run()
{
    createPlayer();
    while (!isGameOver)
    {
        mainMenu();
    }
    std::cout << "\n게임을 종료합니다.\n";
}

void GameManager::createPlayer()
{
    printTitle("캐릭터 생성");
    std::cout << "캐릭 이름을 입력해주세요: ";
    std::string name;
    std::getline(std::cin, name);
    system("cls");
    player = std::make_unique<Character>(name);

    Utils::setConsoleColor(EColor::LightCyan); // 하늘
    std::cout << "\n[" << name << "] 캐릭 생성 완료!\n";
    Utils::setConsoleColor(EColor::White); // 하양

    player->displayStatus();
}

void GameManager::mainMenu()
{
    printTitle("메인 메뉴");
    std::cout << "1. 사냥터로 이동\n";
    std::cout << "2. 캐릭터 상태 확인\n";
    std::cout << "3. 인벤토리 보기\n";
    std::cout << "4. 게임 종료\n";

    int input = getInputRangeInt(1, 4);
    switch (input)
    {
    case 1:
        startBattle();
        break;
    case 2:
        player->displayStatus();
        break;
    case 3:
        player->displayInventory();
        break;
    case 4:
        isGameOver = true;
        break;
    default:
        break;
    }
}

std::unique_ptr<Monster> GameManager::createMonster()
{
    int level = player->getLevel();
    if (level >= 10)
    {
        printSeparator('*', 60);
        std::cout << "         === 최종 보스 출현 ===\n";
        printSeparator('*', 60);
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
        return std::make_unique<Skeleton>(level);
    case 4:
        return std::make_unique<Slime>(level);
    default:
        return std::make_unique<Goblin>(level);
    }
}

void GameManager::startBattle()
{
    auto monster = createMonster();
    printTitle("전투 시작");

    Utils::setConsoleColor(EColor::Red); // 빨강
    std::cout << "몬스터 " << monster->getName() << " 등장! "
        << "체력: " << monster->getHealth() << ", 공격력: " << monster->getAttack() << "\n\n";
    Utils::setConsoleColor(EColor::White); // 하양

    //전투 부분
    while (player->getHealth() > 0 && !monster->isDead())
    {
        Utils::drawMonsterArt(monster->getName());
        printSeparator();
        std::cout << "1. 공격\n";
        std::cout << "2. 아이템 사용\n";
        int input = getInputRangeInt(1, 2);

        bool isItemUsed = false;
        if (input == 2)
        {
            if (player->hasItem())
            {
                player->displayInventory();
                std::cout << "사용할 아이템 번호를 선택하세요 (취소: 0 입력): ";
                int itemChoice = getInputRangeInt(0, player->getInventory().size());
                if (itemChoice > 0)
                {
                    player->useItem(itemChoice - 1); // useItem 내부에서 사용 메시지 출력
                    isItemUsed = true;
                }
            }
            else
            {
                std::cout << "사용할 아이템이 없습니다! 공격을 선택합니다.\n";
            }
        }

        if (!isItemUsed)
        {
            // 플레이어 공격
            int playerAttack = player->getAttack();
            monster->takeDamage(playerAttack);

            Utils::setConsoleColor(EColor::Green); // 초록
            std::cout << player->getName() << "이(가) " << monster->getName() << "을(를) 공격합니다! "
                << monster->getName() << " 체력: " << monster->getHealth() << "\n";
            Utils::setConsoleColor(EColor::White); // 하양

            if (monster->isDead()) break;
            isItemUsed = false;
        }

        // 몬스터 공격
        int monsterAttack = monster->getAttack();
        int playerHealthBefore = player->getHealth();
        player->takeDamage(monsterAttack);

        Utils::setConsoleColor(EColor::Red); // 빨강
        std::cout << monster->getName() << "이(가) " << player->getName() << "을(를) 공격합니다! "
            << player->getName() << " 체력: " << playerHealthBefore << " -> " << player->getHealth() << "\n";
        Utils::setConsoleColor(EColor::White); // 하양
    }

    //전투 종료 승리자 확인
    printSeparator();
    if (monster->isDead())
    {
        Utils::setConsoleColor(EColor::Magenta); // 보라
        std::cout << "\n*** " << monster->getName() << " 처치! 전투에서 승리했습니다! ***\n";
        Utils::setConsoleColor(EColor::White); // 하양

        if (dynamic_cast<BossMonster*>(monster.get()))
        {
            printTitle("게임 클리어");
            std::cout << "보스 " << monster->getName() << "을(를) 처치하고 게임을 클리어했습니다!\n";
            isGameOver = true;
            return;
        }

        int goldAmount = Utils::getRandomInt(10, 20);
        player->addGold(goldAmount);
        player->addExperience(50); // addExperience가 레벨업 및 메시지 처리

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
        printTitle("상점");
        shop.displayShop(*player);
        std::cout << "\n무엇을 하시겠습니까?\n"
            << "1. 아이템 구매\n"
            << "2. 아이템 판매\n"
            << "3. 상점 나가기\n";

        int input = getInputRangeInt(1, 3);

        if (input == 1)
        {
            shop.displayShopItems();
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

        system("cls");
    }
}

void GameManager::printSeparator(char c, int length) const
{
    std::cout << std::string(length, c) << '\n';
}

void GameManager::printTitle(const std::string& title) const
{
    std::cout << "\n";
    printSeparator('=', 50);
    std::cout << " " << title << "\n";
    printSeparator('=', 50);
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

bool GameManager::getInputYesNo() const
{
    char c;
    while (true)
    {
        std::cin >> c;
        system("cls");
        c = std::tolower(c); // 대문자 입력받을 경우 소문자로 변경
        if (c == 'y' || c == 'n')
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return (c == 'y');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "잘못된 입력입니다. Y 또는 N을 입력해주세요: ";
    }
}
