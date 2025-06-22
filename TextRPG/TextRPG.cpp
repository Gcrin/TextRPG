#include "GameManager.h"
#include <iostream>

using namespace std;

int main() 
{
    // 게임 매니저 생성 및 시작
    GameManager* game = GameManager::getInstance();
    game->startGame();

    cout << "게임 종료!" << endl;

    // 싱글톤 인스턴스 정리
    GameManager::destroyInstance();

    return 0;
}