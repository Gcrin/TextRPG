#include "BossMonster.h"
#include "Item.h"

BossMonster::BossMonster(int level) : Name("Goblin"), Health(level * 20), Attack(level * 5) {}

void BossMonster::TakeDamage(int damage)
{
	Health -= damage;
}

Item* BossMonster::DropItem()
{
	return nullptr;
}
