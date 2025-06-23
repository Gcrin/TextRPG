#include "Monster.h"
#include <stdlib.h>
#include <time.h>


Goblin::Goblin(int level)
{
	srand(time(NULL));
	health = level * ((rand() % 11) + 20);
	attack = level * ((rand() % 6) + 5);
}

string Goblin::getName() { return name; }
int Goblin::getHealth() { return health; }
int Goblin::getAttack() { return attack; }
void Goblin::takeDamage(int damage)
{
	health = health - damage;
}