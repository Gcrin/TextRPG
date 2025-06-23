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
	std::cout << "=====" << name << "�� ���� =====\n";
	std::cout << "����: " << level << " | ü��: " << health << "/" << maxHealth 
		<< " | ���ݷ�: " << attack << " | ����ġ: " 
		<< experience<< " | ���: " << gold << "\n";
}

void Character::addExperience(int exp) {
	const int exp = 50;
	experience += exp;
	std::cout << exp << "����ġ�� ������ϴ�.\n";

	if (experience >= 100) {
		experience -= 100;
		levelUp();
	}
}

void Character::levelUp() {
	level++;
	maxHealth += level*20;
	health = maxHealth; // ü�� ȸ��
	attack += level*5;
	std::cout << name << "��(��) �������߽��ϴ�! ���� ����: " << level << "\n";
}

void Character::takeDamage(int damage) {
	health -= damage;
	if (health < 0) health = 0; // ü���� 0 ���Ϸ� �������� �ʵ���
	std::cout << name << "��(��) " << damage << "�� ���ظ� �Ծ����ϴ�. ���� ü��: " << health << "\n";
}

bool Character::isAlive() const {
	return health > 0;
}

void Character::addGold(int amount) {
	gold += amount;
	std::cout << amount << "��带 ������ϴ�. ���� ���: " << gold << "\n";
}
void Character::useItem(int index) {
	if(index < 0 || index >= inventory.size()) {
		std::cout << "�߸��� ������ �ε����Դϴ�.\n";
		return;
	}

	inventory[index]->use(this);
	delete inventory[index]; // ������ ��� �� ����
	inventory.erase(inventory.begin() + index);
}

void Character::addItem(Item* item) {
	inventory.push_back(item);
	std::cout << item->getName() << "�� ȹ���߽��ϴ�.\n";
}

std::vector<Item*> Character::getInventory() {
	return inventory;
}

std::string Character::getName() const { return name; }
int Character::getLevel() const { return level; }
int Character::getAttack() const { return attack; }
int Character::getHealth() const { return health; }
int Character::getGold() const { return gold; }