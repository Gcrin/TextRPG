#include "Troll.h"
#include "Item.h"

Troll::Troll(int level) : Name("Goblin"), Health(level * 20), Attack(level * 10) {}

void Troll::TakeDamage(int damage)
{
	Health -= damage;
}

Item* Troll::DropItem()
{
	return nullptr;
}
