#include "Character.h"
#include <iostream>

Character* Character::instance = nullptr;	
Character::Character(const std::string& name)
	: name(name), level(1), health(200), maxHealth(200), attack(30), experience(0), gold(0) {}

Character* Character::getInstance(const std::string& name) {
	if (instance && !name.empty()) 
		instance = new Character(name);
		return instance;
}

