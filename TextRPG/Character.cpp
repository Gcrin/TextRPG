#include "Character.h"
#include "Shop.h"

Character::Character(string name)
{

}

Character* Character::getInstance(string name = "")
{

}

void Character::displayStatus()
{
	cout << "레벨: " << level << ", 체력: " << health << ", 공격력: " << attack;
}

void Character::levelUp()
{
	level++;
	maxHealth = maxHealth + (level*20);
	attack = attack + (level*5);
	health = maxHealth;
}

void Character::useItem(int index)
{

}

void Character::visitShop()
{
	Shop::displayItem;
}