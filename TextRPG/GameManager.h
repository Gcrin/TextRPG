#pragma once

#include <string>
#include <memory>

using namespace std;

class Character;
class Monster;
class Shop;

class GameManager
{
public:
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    static GameManager* getInstance();
    static void destroyInstance();

    ~GameManager();

    // 게임 진행 함수
    void startGame();

    // 랜덤 몬스터 생성
    unique_ptr<Monster> generateMonster(int level);

    // 보스 몬스터 생성
    unique_ptr<Monster> generateBossMonster(int level);

    // 전투 로직
    void battle(Character* player, Monster* monster);

    // 인벤토리 상태 출력 (TODO: 삭제 예정)
    void visitShop(Character* player);

    // 랜덤 기능 함수
    void initializeRandomSeed();
    int getRandomInt(int min, int max);
    bool getRandomChance(int percentage);

private:
    GameManager();

    bool askVisitShop() const;

    static unique_ptr<GameManager> instance;

    Character* player;
    unique_ptr<Monster> currentMonster;
    unique_ptr<Shop> shop;
    bool randomSeedInitialized;
};