#include "Item.h"

string HealthPotion::getName()
{
	return name;
}

void HealthPotion::use(Character* character)
{
	// ü���� 50 ȸ���� �� ������ 50ȸ��
	if (character->health <= character->maxHealth - healthRestore) {
		character->health += healthRestore;
	}
	// ü���� 50 ȸ���� �� ������ �ִ�ü�±��� ȸ��
	else {
		character->health = character->maxHealth;
	}
	cout << character->name << "�� " << name << "�� ����߽��ϴ�. " << character->name << " ü��: " << character->health << "\n";
}

string AttackBoost::getName()
{
	return name;
}

void AttackBoost::use(Character* character)
{
	//���ݷ� 10 �ø�
	character->attack += AttackIncrease;
	cout << character->name << "�� " << name << "�� ����߽��ϴ�. " << character->name << " ���ݷ�: " << character->attack << "\n";
}