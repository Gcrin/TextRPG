#include "Character.h"
#include "Item.h"  
#include <iostream>
#include <algorithm>

using namespace std;

// static 멤버 초기화
unique_ptr<Character> Character::instance = nullptr;

Character::Character() : name(""), level(1), health(200), maxHealth(200),
attack(30), experience(0), gold(0), additionalAttackAmount(0)
{

}

Character::Character(const string& characterName)
    : name(characterName), level(1), health(200), maxHealth(200),
    attack(30), experience(0), gold(0), additionalAttackAmount(0)
{

}

// 싱글톤 인스턴스 반환
Character* Character::getInstance(const string& name) 
{
    if (instance == nullptr) 
    {
        instance = unique_ptr<Character>(new Character());  
        if (!name.empty()) 
        {
            instance->initialize(name);
        }
    }
    return instance.get();
}


void Character::destroyInstance()
{
    // 싱글톤 인스턴스 해제
    instance = nullptr;
}

Character::~Character() 
{
    // 인벤토리의 모든 아이템 메모리 해제
    inventory.clear();
}

void Character::initialize(const string& characterName) 
{
    name = characterName;
 
    inventory.clear();
    itemCounts.clear();
}

void Character::setHealth(int newHealth) 
{
    health = min(newHealth, maxHealth);
    if (health < 0) health = 0;
}

void Character::spendGold(int amount) 
{
    if (gold >= amount) 
    {
        gold -= amount;
    }
    else 
    {
        cout << "골드가 부족합니다! 현재 골드: " << gold << endl;
    }
}

void Character::takeDamage(int damage)
{
    health -= damage;
    if (health < 0) health = 0;
}

void Character::heal(int amount) 
{
    health = min(health + amount, maxHealth);
}

void Character::addExperience(int exp) 
{
    experience += exp;
    cout << name << "이(가) " << exp << " 경험치를 획득했습니다! "
        << "현재 경험치: " << experience << "/100" << endl;

    // 레벨업 체크(초과 exp 고려)
    while (canLevelUp()) 
    {
        levelUp();
    }
}

void Character::addGold(int amount)
{
    gold += amount;

    cout << name << "이(가) " << amount << " 골드를 획득했습니다!" 
        << "현재 골드: " << gold << endl;
}

void Character::levelUp() 
{
    if (!canLevelUp()) return;

    level++;
    experience -= 100; 

    // 스탯 증가 계산
    int healthIncrease = level * 20;
    int attackIncrease = level * 5;

    // 최대 체력 증가
    maxHealth += healthIncrease;
    attack += attackIncrease;

    // 체력 완전 회복
    health = maxHealth;

    cout << "레벨업! " << name << "이(가) 레벨 " << level << "이(가) 되었습니다!" << endl;
}

void Character::addItem(unique_ptr<Item> item) 
{
    if (item != nullptr)
    {      
        cout << "아이템 '" << item->getName() << "'을(를) 획득했습니다!" << endl;
        
        itemCounts[item->getName()]++; // 아이템 카운트 증가
        inventory.push_back(move(item)); // 소유권 이전       
    }
}

bool Character::hasItem(const string& itemName) const
{
    auto it = itemCounts.find(itemName);
    return it != itemCounts.end() && it->second > 0;
}

bool Character::tryUseItem(const string& itemName)
{
    // 먼저 보유 체크
    if (!hasItem(itemName))
    {
        return false; 
    }

    // 인벤토리에서 해당 아이템 찾아서 사용
    for (int i = 0; i < inventory.size(); ++i)
    {
        if (inventory[i]->getName() == itemName)
        {
            cout << name << "이(가) " << inventory[i]->getName() << "을(를) 사용했습니다!" << endl;
            inventory[i]->use(this);
            removeItem(i);

            // 실시간 카운트 감소
            itemCounts[itemName]--;
            if (itemCounts[itemName] <= 0)
            {
                itemCounts.erase(itemName); 
            }

            return true; 
        }
    }

    return false;  
}

void Character::removeItem(int index)
{
    if (index < 0 || index >= inventory.size())
    {
        cout << "잘못된 아이템 인덱스입니다!" << endl;
        return;
    }

    string itemName = inventory[index]->getName();

    // 인벤토리에서 아이템 제거
    inventory.erase(inventory.begin() + index);

    // 아이템 카운트 감소
    itemCounts[itemName]--;
    if (itemCounts[itemName] <= 0)
    {
        itemCounts.erase(itemName);
    }
}

// 전투 종료후 캐릭터 상태 출력
void Character::displayStatus() const
{
    cout << "=== 캐릭터 상태 ===" << endl;
    cout << "이름: " << name << endl;
    cout << "레벨: " << level << " (최대: 10)" << endl;
    cout << "체력: " << health << "/" << maxHealth << endl;
    cout << "공격력: " << attack << endl;
    cout << "경험치: " << experience << "/100" << endl;
    cout << "골드: " << gold << endl;

    if (hasItems())
    {
        cout << "인벤토리 (" << inventory.size() << "개): ";
        for (size_t i = 0; i < inventory.size(); ++i)
        {
            cout << inventory[i]->getName();
            if (i < inventory.size() - 1) cout << ", ";
        }
        cout << endl;
    }
    else 
    {
        cout << "인벤토리: 비어있음" << endl;
    }
    cout << "==================" << endl;
}