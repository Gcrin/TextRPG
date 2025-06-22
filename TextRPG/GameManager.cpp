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
    cout << "캐릭터 이름을 입력하세요: ";
    cin >> name;
    createCharacter(name);

    while (player->getLevel() <= 10) {
        player->displayStatus();
        battle();
    }

    setConsoleColor(13);
    cout << "\n축하합니다! 보스를 물리치고 게임을 클리어했습니다!\n";
    setConsoleColor(7);
}

void GameManager::createCharacter(const string& name)
{
    player = make_unique<Character>(name);
    setConsoleColor(11);
    cout << "\n[캐릭터 생성 완료] " << name << "\n";
    setConsoleColor(7);
}

void displayBattleLog(const string& playerName, Monster* monster, int damageToMonster, int monsterHealth, int damageToPlayer, int playerHealth) {
    setConsoleColor(10);
    cout << playerName << "가 " << monster->getName() << "을(를) 공격합니다! " << monster->getName() << " 체력: " << monsterHealth << endl;

    if (monsterHealth > 0) {
        setConsoleColor(12);
        cout << monster->getName() << "이(가) " << playerName << "를 공격합니다! " << playerName << " 체력: " << playerHealth << endl;
    }
    else {
        setConsoleColor(13);
        cout << playerName << "가 " << monster->getName() << "을(를) 처치했습니다!" << endl;
    }
    setConsoleColor(7);
}

void GameManager::battle() {
    if (!player) return;
    unique_ptr<Monster> monster = generateMonster(player->getLevel());

    setConsoleColor(12);
    cout << "\n[전투 시작] 몬스터 등장: " << monster->getName() << " (HP: " << monster->getHealth() << ", ATK: " << monster->getAttack() << ")\n";
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
            cout << "\n축하합니다! 보스 " << monster->getName() << "을 처치하고 게임을 클리어했습니다!\n";
            setConsoleColor(7);
            exit(0);
        }

        int goldEarned = 10 + rand() % 11;
        setConsoleColor(14);
        cout << "\n[전투 승리!] 경험치 +50, 골드 +" << goldEarned << "\n";
        player->gainExperience(50);
        player->gainGold(goldEarned);
        cout << "현재 EXP: " << player->getExperience() << "/100, 골드: " << player->getGold() << endl;
        setConsoleColor(7);

        shop.incrementCounter();
        if (shop.shouldOpen()) {
            char enter;
            while (true) {
                cout << "\n[상점 입장 가능] 상점에 진입하시겠습니까? (Y/N): ";
                cin >> enter;
                if (enter == 'Y' || enter == 'y') {
                    shop.open(player.get());
                    break;
                }
                else if (enter == 'N' || enter == 'n') {
                    cout << "상점을 건너뜁니다.\n";
                    break;
                }
                else if (enter == 'D' || enter == 'd') {
                    cout << "사망하시죠...\n";
                    player->takeDamage(1972);
                    break;
                }
                else {
                    cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
                    cout << "\nEnter 키를 누르면 계속...";
                    cin.ignore(); cin.get();
                }

                clearConsole();
            }
        }

        cout << "\nEnter 키를 누르면 계속...";
        cin.ignore(); cin.get();
        clearConsole();
    }
    else {
        setConsoleColor(12);
        cout << "\n[패배] 캐릭터가 쓰러졌습니다...\n";
        setConsoleColor(7);
        exit(0);
    }
}

