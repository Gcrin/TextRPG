#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "Item.h"
#include "Shop.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

unique_ptr<GameManager> GameManager::instance = nullptr;

GameManager::GameManager() : player(nullptr), currentMonster(nullptr), shop(nullptr), randomSeedInitialized(false) 
{
}

GameManager* GameManager::getInstance() 
{
    if (instance == nullptr) 
    {
        instance = unique_ptr<GameManager>(new GameManager());
        instance->initializeRandomSeed();
        instance->shop = make_unique<Shop>();
    }
    return instance.get();
}

void GameManager::destroyInstance()
{
    instance = nullptr;
}

GameManager::~GameManager() 
{
    currentMonster = nullptr;
    shop = nullptr;

    Character::destroyInstance();
}

// 게임 로직
void GameManager::startGame()
{
    string name;

    // 유효한 이름이 입력될 때까지 반복
    while (true) 
    {
        cout << "캐릭터 이름을 입력하세요: ";
        getline(cin, name);

        // 공백일 경우 재입력 요구
        if (name.empty() || name.find(' ') != string::npos) 
        {
            cout << "이름에는 공백을 포함할 수 없습니다! 다시 입력해주세요." << endl;
            continue;
        }

        break;
    }

    // 캐릭터 생성
    player = Character::getInstance(name);
    cout << "캐릭터 " << name << " 생성 완료! 레벨: " << player->getLevel()
        << ", 체력: " << player->getHealth() << ", 공격력: " << player->getAttack() << endl;

    // 게임 실행 루프
    while (player->isAlive() && player->getLevel() < 10) 
    {
        // 몬스터 생성 및 전투
        currentMonster = generateMonster(player->getLevel());
        battle(player, currentMonster.get());

        if (!player->isAlive())
        {
            break;
        }
        currentMonster = nullptr;

        // 상점 방문 여부 확인
        if (askVisitShop())
        {
            visitShop(player);
        }

        // 현재 상태 표시
        player->displayStatus();
    }

    // 보스전 시작
    while (player->isAlive() && player->getLevel() >= 10)
    {
        cout << "\n레벨 10에 도달했습니다!" << endl;
        cout << "강력한 보스 몬스터가 등장합니다!" << endl;

        // 보스 몬스터 생성 및 전투
        currentMonster = generateBossMonster(player->getLevel());
        battle(player, currentMonster.get());

        if (!player->isAlive())
        {
            break;
        }
        currentMonster = nullptr;
        break; 
    }

    if (!player->isAlive())
    {
        cout << "\n게임 오버!" << endl;
    }
    else
    {
        cout << "\n게임 클리어! " << endl;
    }
    cout << "\n최종 결과:" << endl;
    player->displayStatus();
}

unique_ptr<Monster> GameManager::generateMonster(int level)
{
    return Monster::createRandomMonster(level);
}

unique_ptr<Monster> GameManager::generateBossMonster(int level)
{
    return BossMonster::createBossMonster(level);
}

// 전투 로직
void GameManager::battle(Character* player, Monster* monster)
{
    cout << "몬스터 " << monster->getName() << " 등장! 체력: " << monster->getHealth()
        << ", 공격력: " << monster->getAttack() << endl;

    // 턴제 전투
    while (player->isAlive() && monster->isAlive()) 
    {
        // Reset관련 로직 많아지면 player->reset 같은 함수로 필요한 변수들 리셋
        player->resetAdditionalAttackAmount();

        // 플레이어 턴  
        // 20% 확률로 attackboost 사용
        if (getRandomChance(20) && player->hasItem("AttackBoost")) 
        {  
            cout << "이럴 때 아이템!" << endl;
            player->tryUseItem("AttackBoost");
        }
        int baseDamage = player->getAttack();
        int additionalDamage = player->getAdditionalAttackAmount();
        int totalDamage = baseDamage + additionalDamage;

        int oldMonsterHealth = monster->getHealth();
        monster->takeDamage(totalDamage);
        cout << player->getName() << "가 " << monster->getName() << "을 공격합니다! "
            << monster->getName() << " 체력: " << oldMonsterHealth << " -> " << monster->getHealth() << endl;

        if (!monster->isAlive()) 
        {
            cout << monster->getName() << " 처치!" << endl;
            break;
        }

        // 몬스터 턴
        int oldPlayerHealth = player->getHealth();
        int monsterDamage = monster->getAttack();

        // 피격 후 사망할 체력이면 30% 확률로 HealthPotion 사용
        if (oldPlayerHealth - monsterDamage <= 0 && getRandomChance(30) && player->hasItem("HealthPotion")) 
        {  
            cout << "이럴 때 아이템!" << endl;
            player->tryUseItem("HealthPotion");
            oldPlayerHealth = player->getHealth();  // 회복 후 체력으로 업데이트
        }

        player->takeDamage(monsterDamage);
        cout << monster->getName() << "이 " << player->getName() << "을 공격합니다! "
            << player->getName() << " 체력: " << oldPlayerHealth << " → " << player->getHealth() << endl;

        if (!player->isAlive()) 
        {
            cout << player->getName() << "가 사망했습니다." << endl;
            return;
        }
    }

    // 전투 승리 보상
    if (player->isAlive()) 
    {
        // 경험치 50 획득
        player->addExperience(50);

        // 골드 10~20 랜덤 획득
        int gold = getRandomInt(10, 20);
        player->addGold(gold);

        // 30% 확률로 아이템 드롭
        if (getRandomChance(30)) 
        {
            unique_ptr<Item> item = Item::createRandomItem();
            player->addItem(move(item));
        }
    }
}

// 상점 방문 로직
void GameManager::visitShop(Character* player)
{
    if (shop == nullptr)
    {
        cout << "상점이 준비되지 않았습니다!" << endl;
        return;
    }

    if (player == nullptr)
    {
        cout << "플레이어가 유효하지 않습니다!" << endl;
        return;
    }

    // Shop 클래스의 visitShop 함수에서 상세 동작
    shop->visitShop(player);
}

bool GameManager::askVisitShop() const
{
    cout << "\n상점을 방문하시겠습니까? (Y/N): ";
    char choice;
    cin >> choice;

    // 입력 버퍼 클리어
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return (choice == 'Y' || choice == 'y');
}

void GameManager::initializeRandomSeed()
{
    if (!randomSeedInitialized) 
    {
        srand(time(nullptr));
        randomSeedInitialized = true;
    }
}

// 지정한 범위 내 랜덤 정수 생성
int GameManager::getRandomInt(int min, int max)
{
    if (min > max) 
    {
        swap(min, max);
    }
    return min + (rand() % (max - min + 1));
}

bool GameManager::getRandomChance(int percentage)
{
    if (percentage <= 0) return false;
    if (percentage >= 100) return true;
    return (rand() % 100) < percentage;
}
