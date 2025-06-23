#include "Item.h"

string HealthPotion::getName()
{
	return name;
}

void HealthPotion::use(Character* character)
{
	// 체력이 50 회복할 수 있으면 50회복
	if (character->health <= character->maxHealth - healthRestore) {
		character->health += healthRestore;
	}
	// 체력을 50 회복할 수 없으면 최대체력까지 회복
	else {
		character->health = character->maxHealth;
	}
	cout << character->name << "가 " << name << "을 사용했습니다. " << character->name << " 체력: " << character->health << "\n";
}

string AttackBoost::getName()
{
	return name;
}

void AttackBoost::use(Character* character)
{
	//공격력 10 올림
	character->attack += AttackIncrease;
	cout << character->name << "가 " << name << "을 사용했습니다. " << character->name << " 공격력: " << character->attack << "\n";
}