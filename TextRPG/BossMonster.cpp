#include "BossMonster.h"
#include <string>
#include <stdlib.h>
#include <time.h>


using namespace std;


BossMonster::BossMonster(int level)
{
	name = getName();
	health = level * getHealth();
	attack = level * getAttack();
}

string BossMonster::getName()
{
	string name;
	name = "Troll";
	return name;
}

int BossMonster::getHealth()
{
	int Health;

	srand(time(NULL));
	Health = ((rand() % 11) + 20)*1.5;

	return Health;
}

int BossMonster::getAttack()
{
	int attack;

	srand(time(NULL));
	attack = ((rand() % 6) + 5)*1.5;

	return attack;
}

void BossMonster::takeDamage(int damage)
{
	health -= damage;
}

Item* BossMonster::dropItem()
{

}