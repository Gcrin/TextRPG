#include "shop.h"
#include "Item.h"
#include "ui_utils.h"
#include <iostream>
#include <limits>
using namespace std;

bool Shop::shouldOpen() {
    return visitCounter > 0 && visitCounter % 3 == 0;
}

void Shop::incrementCounter() {
    visitCounter++;
}

void Shop::open(Character* player) {
    while (true) {
        clearConsole();

        cout << "\n상점에 오신 것을 환영합니다!\n";
        cout << "보유 골드: " << player->getGold() << "\n";
        cout << "1. 아이템 구매\n";
        cout << "2. 아이템 판매\n";
        cout << "0. 나가기\n";
        cout << "선택: ";
        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "숫자를 입력해주세요. 다시 시도하세요.\n";
            cout << "\nEnter 키를 누르면 계속...";
            cin.ignore(); cin.get();
            continue;
        }

        if (choice == 0) {
            cout << "상점에서 나갑니다.\n";
            break;
        }
        else if (choice == 1) {
            clearConsole();
            cout << "1. Health Potion (체력 +50): 10 골드\n";
            cout << "2. Attack Boost (공격력 +10): 15 골드\n";
            cout << "보유 골드: " << player->getGold() << "\n";
            cout << "구매할 아이템 번호를 선택하세요 (0: 취소): ";
            int buy;
            cin >> buy;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "숫자를 입력해주세요. 다시 시도하세요.\n";
                cout << "\nEnter 키를 누르면 계속...";
                cin.ignore(); cin.get();
                continue;
            }

            if (buy == 0) {
                cout << "구매를 취소했습니다.\n";
            }
            else if (buy == 1 && player->getGold() >= 10) {
                player->addItem(make_unique<HealthPotion>());
                player->gainGold(-10);
                cout << "Health Potion을 구매했습니다!\n";
            }
            else if (buy == 2 && player->getGold() >= 15) {
                player->addItem(make_unique<AttackBoost>());
                player->gainGold(-15);
                cout << "Attack Boost를 구매했습니다!\n";
            }
            else {
                cout << "잘못된 입력이거나 골드가 부족합니다. 다시 시도하세요.\n";
            }

            cout << "\nEnter 키를 누르면 계속...";
            cin.ignore(); cin.get();
        }
        else if (choice == 2) {
            clearConsole();
            cout << "[인벤토리 목록]\n";
            player->showInventory();
            if (player->getInventorySize() == 0) {
                cout << "판매할 아이템이 없습니다.\n";
                cout << "\nEnter 키를 누르면 계속...";
                cin.ignore(); cin.get();
                continue;
            }
            cout << "판매할 아이템 번호를 선택하세요 (0: 취소): ";
            int sellIndex;
            cin >> sellIndex;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "숫자를 입력해주세요. 다시 시도하세요.\n";
                cout << "\nEnter 키를 누르면 계속...";
                cin.ignore(); cin.get();
                continue;
            }

            if (sellIndex == 0) continue;

            int goldEarned = 0;
            if (player->sellItem(sellIndex - 1, goldEarned)) {
                cout << goldEarned << " 골드를 획득했습니다.\n";
            }
            else {
                cout << "판매에 실패했습니다.\n";
            }

            cout << "\nEnter 키를 누르면 계속...";
            cin.ignore(); cin.get();
        }
        else {
            cout << "잘못된 입력입니다. 다시 시도하세요.\n";
            cout << "\nEnter 키를 누르면 계속...";
            cin.ignore(); cin.get();
        }
    }
}
