#include "Orc.h"
#include <string>
#include <stdlib.h>
#include <time.h>


using namespace std;


Orc::Orc(int level)
{
	name = getName();
	health = level * getHealth();
	attack = level * getAttack();
}

string Orc::getName()
{
	string name;
	name = "Orc";
	return name;
}

int Orc::getHealth()
{
	int Health;

	srand(time(NULL));
	Health = (rand() % 11) + 20;

	return Health;
}

int Orc::getAttack()
{
	int attack;

	srand(time(NULL));
	attack = (rand() % 6) + 5;

	return attack;
}

void Orc::takeDamage(int damage)
{
	health -= damage;
}

Item* Orc::dropItem()
{

}