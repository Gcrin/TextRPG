#ifdef _WIN32

#include "Monster.h"
#include <windows.h>

#include <cstdlib>
#include <iostream>

#endif

Monster::Monster(const string& name, int health, int attack)
    : name(name), health(health), attack(attack) {
}

string Monster::getName() const { return name; }

int Monster::getHealth() const { return health; }
int Monster::getAttack() const { return attack; }

void Monster::takeDamage(int damage) { health -= damage; if (health < 0) health = 0; }

Goblin::Goblin(int level) : Monster("Goblin", level * 20 + rand() % (level * 11), level * 5 + rand() % (level * 6)) { }
Orc::Orc(int level) : Monster("Orc", level * 22 + rand() % (level * 12), level * 6 + rand() % (level * 5)) { }
Skeleton::Skeleton(int level): Monster("Skeleton", level * 25 + rand() % (level * 10), level * 6 + rand() % (level * 7)) { }
Slime::Slime(int level) : Monster("Slime", level * 18 + rand() % (level * 15), level * 4 + rand() % (level * 6)) { }

Boss::Boss(int level) : Monster("Dragon", level * 30 + rand() % (level * 15), level * 10 + rand() % (level * 8)) { }
