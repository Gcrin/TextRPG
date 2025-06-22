#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>
using namespace std;

class Character;
class Item;

class Shop
{
public:
    Shop();

    ~Shop() = default;

    // 상점 메인 메뉴
    void visitShop(Character* player);

    void buyItem(Character* player);
    void sellItem(Character* player);

    // 상점 아이템 목록 표시
    void displayItems() const;

    // 플레이어 인벤토리 표시 (판매용)
    void displayPlayerInventory(Character* player) const;

private:
    // 판매 가격 계산 (구매가의 60%)
    int getSellPrice(const string& itemName) const;

    unique_ptr<Item> createItemByName(const string& itemName) const;

private:
    // 아이템 가격 정보 저장
    unordered_map<string, int> itemPrices;

};