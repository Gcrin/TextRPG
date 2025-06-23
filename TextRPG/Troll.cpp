#include "Troll.h"
#include <string>
#include <stdlib.h>
#include <time.h>


using namespace std;


Troll::Troll(int level)
{
	name = getName();
	health = level * getHealth();
	attack = level * getAttack();
}

string Troll::getName()
{
	string name;
	name = "Troll";
	return name;
}

int Troll::getHealth()
{
	int Health;

	srand(time(NULL));
	Health = (rand() % 11) + 20;

	return Health;
}

int Troll::getAttack()
{
	int attack;

	srand(time(NULL));
	attack = (rand() % 6) + 5;

	return attack;
}

void Troll::takeDamage(int damage)
{
	health -= damage;
}

Item* Troll::dropItem()
{

}