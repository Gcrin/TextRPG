#include <iostream>
#include "GameManager.h"
#include "Character.h"


int main() {
	std::string playerName;

	std::cout << "당신의 이름을 입력하세요: ";
	std::cin >> playerName;

	Character::getInstance(playerName);

	GameManager game;
	game.start();

	return 0;
}