#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "Item.h"
#include "shop.h"
#include "ui_utils.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

unique_ptr<Monster> GameManager::generateMonster(int level) {
    if (level == 10) {
        return make_unique<Boss>(level);
    }
    int r = rand() % 4;
    switch (r) {
    case 0: return make_unique<Goblin>(level);
    case 1: return make_unique<Orc>(level);
    case 2: return make_unique<Skeleton>(level);
    default: return make_unique<Slime>(level);
    }
}

void GameManager::run() {
    srand((unsigned)time(0));
    string name;
    cout << "ĳ���� �̸��� �Է��ϼ���: ";
    cin >> name;
    createCharacter(name);

    while (player->getLevel() <= 10) {
        player->displayStatus();
        battle();
    }

    setConsoleColor(13);
    cout << "\n�����մϴ�! ������ ����ġ�� ������ Ŭ�����߽��ϴ�!\n";
    setConsoleColor(7);
}

void GameManager::createCharacter(const string& name)
{
    player = make_unique<Character>(name);
    setConsoleColor(11);
    cout << "\n[ĳ���� ���� �Ϸ�] " << name << "\n";
    setConsoleColor(7);
}

void displayBattleLog(const string& playerName, Monster* monster, int damageToMonster, int monsterHealth, int damageToPlayer, int playerHealth) {
    setConsoleColor(10);
    cout << playerName << "�� " << monster->getName() << "��(��) �����մϴ�! " << monster->getName() << " ü��: " << monsterHealth << endl;

    if (monsterHealth > 0) {
        setConsoleColor(12);
        cout << monster->getName() << "��(��) " << playerName << "�� �����մϴ�! " << playerName << " ü��: " << playerHealth << endl;
    }
    else {
        setConsoleColor(13);
        cout << playerName << "�� " << monster->getName() << "��(��) óġ�߽��ϴ�!" << endl;
    }
    setConsoleColor(7);
}

void GameManager::battle() {
    if (!player) return;
    unique_ptr<Monster> monster = generateMonster(player->getLevel());

    setConsoleColor(12);
    cout << "\n[���� ����] ���� ����: " << monster->getName() << " (HP: " << monster->getHealth() << ", ATK: " << monster->getAttack() << ")\n";
    setConsoleColor(7);
    drawMonsterArt(monster->getName());

    while (player->isAlive() && monster->getHealth() > 0) {
        int damageToMonster = player->getAttack();
        monster->takeDamage(damageToMonster);
        int monsterHealth = monster->getHealth();

        int damageToPlayer = 0;
        if (monsterHealth > 0) {
            damageToPlayer = monster->getAttack();
            player->takeDamage(damageToPlayer);
        }

        displayBattleLog(player->getName(), monster.get(), damageToMonster, monsterHealth, damageToPlayer, player->getHealth());
    }

    if (player->isAlive()) {
        if (player->getLevel() == 10 && monster->getName() == "Dragon") {
            setConsoleColor(13);
            cout << "\n�����մϴ�! ���� " << monster->getName() << "�� óġ�ϰ� ������ Ŭ�����߽��ϴ�!\n";
            setConsoleColor(7);
            exit(0);
        }

        int goldEarned = 10 + rand() % 11;
        setConsoleColor(14);
        cout << "\n[���� �¸�!] ����ġ +50, ��� +" << goldEarned << "\n";
        player->gainExperience(50);
        player->gainGold(goldEarned);
        cout << "���� EXP: " << player->getExperience() << "/100, ���: " << player->getGold() << endl;
        setConsoleColor(7);

        shop.incrementCounter();
        if (shop.shouldOpen()) {
            char enter;
            while (true) {
                cout << "\n[���� ���� ����] ������ �����Ͻðڽ��ϱ�? (Y/N): ";
                cin >> enter;
                if (enter == 'Y' || enter == 'y') {
                    shop.open(player.get());
                    break;
                }
                else if (enter == 'N' || enter == 'n') {
                    cout << "������ �ǳʶݴϴ�.\n";
                    break;
                }
                else if (enter == 'D' || enter == 'd') {
                    cout << "����Ͻ���...\n";
                    player->takeDamage(1972);
                    break;
                }
                else {
                    cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n";
                    cout << "\nEnter Ű�� ������ ���...";
                    cin.ignore(); cin.get();
                }

                clearConsole();
            }
        }

        cout << "\nEnter Ű�� ������ ���...";
        cin.ignore(); cin.get();
        clearConsole();
    }
    else {
        setConsoleColor(12);
        cout << "\n[�й�] ĳ���Ͱ� ���������ϴ�...\n";
        setConsoleColor(7);
        exit(0);
    }
}

