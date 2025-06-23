#include "Character.h"
#include <iostream>

Character* Character::instance = nullptr;	
Character::Character(const std::string& name)
	: name(name), level(1), health(200), maxHealth(200), attack(30), experience(0), gold(0) {}

Character* Character::getInstance(const std::string& name) {
	if (instance && !name.empty()) {
		instance = new Character(name);
	}
	return instance;
}

void Character::displayStatus() const {
	std::cout << "=====" << name << "의 상태 =====\n";
	std::cout << "레벨: " << level << " | 체력: " << health << "/" << maxHealth 
		<< " | 공격력: " << attack << " | 경험치: " 
		<< experience<< " | 골드: " << gold << "\n";
}

void Character::addExperience(int exp) {
	const int exp = 50;
	experience += exp;
	std::cout << exp << "경험치를 얻었습니다.\n";

	if (experience >= 100) {
		experience -= 100;
		levelUp();
	}
}

void Character::levelUp() {
	level++;
	maxHealth += level*20;
	health = maxHealth; // 체력 회복
	attack += level*5;
	std::cout << name << "이(가) 레벨업했습니다! 현재 레벨: " << level << "\n";
}

void Character::takeDamage(int damage) {
	health -= damage;
	if (health < 0) health = 0; // 체력이 0 이하로 떨어지지 않도록
	std::cout << name << "이(가) " << damage << "의 피해를 입었습니다. 현재 체력: " << health << "\n";
}

bool Character::isAlive() const {
	return health > 0;
}

void Character::addGold(int amount) {
	gold += amount;
	std::cout << amount << "골드를 얻었습니다. 현재 골드: " << gold << "\n";
}
void Character::useItem(int index) {
	if(index < 0 || index >= inventory.size()) {
		std::cout << "잘못된 아이템 인덱스입니다.\n";
		return;
	}

	inventory[index]->use(this);
	delete inventory[index]; // 아이템 사용 후 삭제
	inventory.erase(inventory.begin() + index);
}

void Character::addItem(Item* item) {
	inventory.push_back(item);
	std::cout << item->getName() << "을 획득했습니다.\n";
}

std::vector<Item*> Character::getInventory() {
	return inventory;
}

std::string Character::getName() const { return name; }
int Character::getLevel() const { return level; }
int Character::getAttack() const { return attack; }
int Character::getHealth() const { return health; }
int Character::getGold() const { return gold; }