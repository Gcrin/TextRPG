#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

using namespace std;

class Item;

class Character
{
public:

    // 복사 생성자, 대입 연산자 삭제 함수로 지정하여 싱글톤 보장
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;

    // 추후 상속 구조 고려
    virtual ~Character();

    // 싱글톤 패턴 구현
    static Character* getInstance(const string& name = "");
    static void destroyInstance();


    // 캐릭터 생성 초기화
    void initialize(const string& characterName);

    // 캐릭터 플레이 로직
    void takeDamage(int damage);
    void heal(int amount);
    void addExperience(int exp);
    void addGold(int amount);
    void levelUp();
    bool isAlive() const { return health > 0; }
    bool canLevelUp() const { return experience >= 100; }

    // 아이템 관련 로직
    void addItem(unique_ptr<Item> item);
    bool hasItems() const { return !inventory.empty(); }
    bool hasItem(const string& itemName) const;
    bool tryUseItem(const string& itemName);
    void removeItem(int index);

    // 캐릭터 상태 출력
    void displayStatus() const;

    // Setter
    void setName(const string& newName) { name = newName; }
    void setHealth(int newHealth);
    void setAttack(int newAttack) { attack = newAttack; }
    void spendGold(int amount);

    // Getter 
    string getName() const { return name; }
    int getLevel() const { return level; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getAttack() const { return attack; }
    int getAdditionalAttackAmount() const { return additionalAttackAmount; }
    int getExperience() const { return experience; }
    int getGold() const { return gold; }
    const vector<unique_ptr<Item>>& getInventory() const { return inventory; }

    // additionalAttackAmount 함수
    void addAdditionalAttackAmount(int additionalAmount) { additionalAttackAmount += additionalAmount; }
    void resetAdditionalAttackAmount() { additionalAttackAmount = 0; }

private:
    // 싱글톤 패턴을 위한 컴파일러 자동 생성 public 생성자 차단
    Character();
    Character(const string& characterName);

private:
    static unique_ptr<Character> instance;

    string name;
    int level;
    int health;
    int maxHealth;
    int attack;
    int additionalAttackAmount;
    int experience;
    int gold;
    vector<unique_ptr<Item>> inventory;

    // 아이템 타입별 개수
    unordered_map<string, int> itemCounts;
};
