#include "Goblin.h"
#include <string>
#include <stdlib.h>
#include <time.h>


using namespace std;


Goblin::Goblin(int level)
{
	name = getName();
	health = level * getHealth();
	attack = level * getAttack();
}

string Goblin::getName()
{
	string name;
	name = "Goblin";
	return name;
}

int Goblin::getHealth()
{
	int Health;

	srand(time(NULL));
	Health = (rand() % 11)+20;

	return Health;
}

int Goblin::getAttack()
{
	int attack;

	srand(time(NULL));
	attack = (rand() % 6) + 5;

	return attack;
}

void Goblin::takeDamage(int damage)
{
	health -= damage;
}

Item* Goblin::dropItem()
{
	
}