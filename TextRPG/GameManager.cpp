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
    std::cout << "ĳ���� �̸��� �Է��ϼ���: ";
    std::string name;
    std::getline(std::cin, name);
    system("cls");
    player = std::make_unique<Character>(name);
    std::cout << "ĳ���� " << name << " ���� �Ϸ�!";
    player->displayStatus();
}


void GameManager::StartBattle()
{
    auto monster = CreateMonster();
    std::cout << "���� " << monster->getName() << " ����! " << "ü��: " << monster->getHealth() << ", ���ݷ�: " << monster->getAttack() << "\n\n";

    //���� �κ�
    while (player->getHealth() > 0 && !monster->isDead())
    {

        if (Utils::getRandomInt(1, 10) <= 2) // 20% Ȯ���� ������ ���
        {
            if (player->hasItem())
            {
                int itemChoice = Utils::getRandomInt(0, player->getInventory().size());
                player->useItem(itemChoice);
            }
        }

        // �÷��̾� ����
        int playerAttack = player->getAttack();
        monster->takeDamage(playerAttack);
        std::cout << player->getName() << "��(��) " << monster->getName() << "��(��) �����մϴ�! "
            << monster->getName() << " ü��: " << monster->getHealth() << "\n";

        if (monster->isDead()) break;

        // ���� ����
        int monsterAttack = monster->getAttack();
        int playerHealthBefore = player->getHealth();
        player->takeDamage(monsterAttack);
        std::cout << monster->getName() << "��(��) " << player->getName() << "��(��) �����մϴ�! "
            << player->getName() << " ü��: " << playerHealthBefore << " -> " << player->getHealth() << "\n";
    }

    //���� ����

    if (monster->isDead())
    {
        std::cout << "\n*** " << monster->getName() << " óġ! �������� �¸��߽��ϴ�! ***\n";

        if (dynamic_cast<BossMonster*>(monster.get()))
        {
            std::cout << "���� " << monster->getName() << "��(��) óġ�ϰ� ������ Ŭ�����߽��ϴ�!\n";
            isGameOver = true;
            return;
        }

        int goldAmount = Utils::getRandomInt(10, 20);
        player->addGold(goldAmount);
        player->addExperience(50);

        std::cout << "Hero�� 50 EXP�� " << goldAmount << " ��带 ȹ���߽��ϴ�. "
            << "���� EXP: " << player->getExperience() << "/100, ���: " << player->getGold() << "\n";

        auto droppedItem = monster->dropItem();
        if (droppedItem)
        {
            std::cout << "[������]" << droppedItem->getName() << "��(��) ȹ���߽��ϴ�!\n";
            player->addItem(std::move(droppedItem));
        }

        visitShop();
    }
    else
    {
        std::cout << "\n*** " << player->getName() << "��(��) ����߽��ϴ�. ���� ����! ***\n";
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
    std::cout << "\n������ �湮�Ͻðڽ��ϱ�? (Y/N): ";
    if (!getInputYesNo())
    {
        std::cout << "������ ����մϴ�.\n";
        return;
    }
    Shop shop;

    while (true)
    {
        shop.displayShop(*player);
        std::cout << "\n������ �Ͻðڽ��ϱ�?\n"
            << "1. ������ ����\n"
            << "2. ������ �Ǹ�\n"
            << "3. ���� ������\n"
            << "����: ";

        int input = getInputRangeInt(1, 3);

        if (input == 1)
        {
            std::cout << "������ ������ ��ȣ�� �����ϼ��� (���: 0): ";
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
                std::cout << "�Ǹ��� �������� �����ϴ�.\n";
            }
            else
            {
                player->displayInventory();
                std::cout << "�Ǹ��� ������ ��ȣ�� �Է��ϼ��� (���: 0): ";
                int sellInput = getInputRangeInt(0, player->getInventory().size());
                if (sellInput > 0)
                {
                    shop.sellItem(sellInput, *player);
                }
            }
        }
        else if (input == 3)
        {
            std::cout << "�������� ���Խ��ϴ�.\n";
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
        std::cout << "�߸��� �Է��Դϴ�. Y �Ǵ� N�� �Է����ּ���: ";
    }
}

int GameManager::getInputRangeInt(int min, int max) const
{
    int input;
    while (true)
    {
        std::cout << "����: ";
        std::cin >> input;
        system("cls");
        if (std::cin.good() && input >= min && input <= max)
        {
            // ���ۿ� �����ִ� ��� ���빰(�߸��� �Է� + ����Ű)�� ���� �ٹٲ� ����('\n')���� Ȯ���ϰ� ����.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "�߸��� �Է��Դϴ�. " << min << "���� " << max << " ������ ���ڸ� �Է����ּ���.\n";
    }
}