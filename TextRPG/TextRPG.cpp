#include <iostream>
#include "GameManager.h"
#include "Character.h"


int main() {
	std::string playerName;

	std::cout << "����� �̸��� �Է��ϼ���: ";
	std::cin >> playerName;

	Character::getInstance(playerName);

	GameManager game;
	game.start();

	return 0;
}