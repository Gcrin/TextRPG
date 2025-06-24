#pragma once
#include<vector>
#include<memory>

class Item;
class Character;

class Shop
{
private:
    std::vector<std::unique_ptr<Item>> AvailableItems;

public:
    Shop();
    ~Shop();

    
    void DisplayItems() const;
    /**
     * 상점에서 플레이어가 특정 아이템을 구매하는 메서드입니다.
     *
     * @param index 구매하려는 아이템의 인덱스입니다. 아이템 리스트의 유효한 범위 내에 있어야 합니다.
     * @param player 아이템을 구매하려는 플레이어 캐릭터의 포인터입니다.
     */
    void BuyItem(int index, Character* player);
    void SellItem(int index, Character* player);
    void AddItem(std::unique_ptr<Item> item);
};
