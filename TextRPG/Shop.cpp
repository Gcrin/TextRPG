#include "Shop.h"
#include "Character.h"
#include "Item.h"
#include <iostream>
#include <limits>

Shop::Shop()
{
    // 상점 아이템 가격 설정
    itemPrices["HealthPotion"] = 10;
    itemPrices["AttackBoost"] = 15;
}

void Shop::visitShop(Character* player)
{
    if (player == nullptr)
    {
        cout << "플레이어가 유효하지 않습니다!" << endl;
        return;
    }

    cout << "\n=== 상점에 오신 것을 환영합니다! ===" << endl;

    while (true)
    {
        cout << "현재 골드: " << player->getGold() << endl;
        cout << "1. 아이템 구매" << endl;
        cout << "2. 아이템 판매" << endl;
        cout << "3. 상점 나가기" << endl;
        cout << "선택하세요 (1-3): ";

        int choice;
        cin >> choice;

        // 입력 오류 처리
        if (cin.fail())
        {
            // 스트림 에러 상태 플래그 리셋
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "잘못된 입력입니다!" << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            buyItem(player);
            break;
        case 2:
            sellItem(player);
            break;
        case 3:
            cout << "상점을 나갑니다." << endl;
            return;
        default:
            cout << "잘못된 선택입니다! 1-3 중에서 선택해주세요." << endl;
            break;
        }
    }
}

void Shop::buyItem(Character* player)
{
    cout << "\n=== 아이템 구매 ===" << endl;
    displayItems();

    cout << "구매할 아이템 번호를 선택하세요 (0: 취소): ";
    int choice;
    cin >> choice;

    // 입력 오류 처리
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "잘못된 입력입니다!" << endl;
        return;
    }

    if (choice == 0)
    {
        cout << "구매를 취소했습니다." << endl;
        return;
    }

    string itemName;
    int price;

    // 선택에 따라 아이템 결정
    switch (choice)
    {
    case 1:
        itemName = "HealthPotion";
        price = itemPrices[itemName];
        break;
    case 2:
        itemName = "AttackBoost";
        price = itemPrices[itemName];
        break;
    default:
        cout << "잘못된 선택입니다!" << endl;
        return;
    }

    // 골드 확인
    if (player->getGold() < price)
    {
        cout << "골드가 부족합니다! 필요한 골드: " << price
            << ", 현재 골드: " << player->getGold() << endl;
        return;
    }

    // 아이템 생성 및 구매 처리
    unique_ptr<Item> newItem = createItemByName(itemName);
    if (newItem == nullptr)
    {
        cout << "아이템 생성에 실패했습니다!" << endl;
        return;
    }

    // 골드 차감 및 아이템 추가
    player->spendGold(price);
    player->addItem(move(newItem));

    cout << itemName << "을(를) 구매했습니다! (-" << price << " 골드)" << endl;
}

void Shop::sellItem(Character* player)
{
    cout << "\n=== 아이템 판매 ===" << endl;

    if (!player->hasItems())
    {
        cout << "판매할 아이템이 없습니다." << endl;
        return;
    }

    displayPlayerInventory(player);

    cout << "판매할 아이템 번호를 선택하세요 (0: 취소): ";
    int choice;
    cin >> choice;

    // 입력 오류 처리
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "잘못된 입력입니다!" << endl;
        return;
    }

    if (choice == 0)
    {
        cout << "판매를 취소했습니다." << endl;
        return;
    }

    const vector<unique_ptr<Item>>& inventory = player->getInventory();

    if (choice < 1 || choice > inventory.size())
    {
        cout << "잘못된 선택입니다!" << endl;
        return;
    }

    // 선택한 아이템 정보
    int index = choice - 1;
    string itemName = inventory[index]->getName();
    int sellPrice = getSellPrice(itemName);

    if (sellPrice <= 0)
    {
        cout << "이 아이템은 판매할 수 없습니다!" << endl;
        return;
    }

    // 판매 처리
    cout << itemName << "을(를) " << sellPrice << " 골드에 판매했습니다!" << endl;
    player->addGold(sellPrice);
    player->removeItem(index); 
}

void Shop::displayItems() const
{
    cout << "\n구매 가능한 아이템:" << endl;
    int index = 1;

    for (const pair<const string, int>& item : itemPrices)
    {
        string description;
        if (item.first == "HealthPotion")
        {
            description = " (체력 +50)";
        }
        else if (item.first == "AttackBoost")
        {
            description = " (공격력 +10)";
        }

        cout << index << ". " << item.first << description
            << ": " << item.second << " 골드" << endl;
        index++;
    }
}

void Shop::displayPlayerInventory(Character* player) const
{
    const vector<unique_ptr<Item>>& inventory = player->getInventory();

    cout << "\n판매 가능한 아이템:" << endl;

    for (int i = 0; i < inventory.size(); ++i)
    {
        string itemName = inventory[i]->getName();
        int sellPrice = getSellPrice(itemName);

        cout << (i + 1) << ". " << itemName;
        if (sellPrice > 0)
        {
            cout << " (판매가: " << sellPrice << " 골드)";
        }
        else
        {
            cout << " (판매 불가)";
        }
        cout << endl;
    }
}

unique_ptr<Item> Shop::createItemByName(const string& itemName) const
{
    if (itemName == "HealthPotion")
    {
        return make_unique<HealthPotion>();
    }
    else if (itemName == "AttackBoost")
    {
        return make_unique<AttackBoost>();
    }

    return nullptr;  // 알 수 없는 아이템
}

int Shop::getSellPrice(const string& itemName) const
{
    auto it = itemPrices.find(itemName);
    if (it != itemPrices.end())
    {
        // 구매가의 60%로 판매
        return static_cast<int>(it->second * 0.6);
    }
    return 0;  // 판매 불가 아이템
}
