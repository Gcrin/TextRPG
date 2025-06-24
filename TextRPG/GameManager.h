#pragma once
#include <memory>
#include <random>

class Character;
class Monster;
class BossMonster;
class Shop;

class GameManager
{
private:
    std::unique_ptr<Shop> shop;
    int monstersKillCount;
    bool isGameRunning;

    void MainLoop(Character* player);
    void BossBattle(Character* player);
    bool AutoItemUse(Character* player);
    void TurnBasedCombat(Character* player, Monster* monster);
    void ClearConsole();
public:
    GameManager();
    ~GameManager();
    void Run();
    
    std::unique_ptr<Monster> GenerateMonster(int level);
    std::unique_ptr<BossMonster> GenerateBossMonster(int level);
    void Battle(Character* player);
    void VisitShop(Character* player);
};
