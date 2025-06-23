#include "Orc.h"
#include "Item.h"

Orc::Orc(int level) : Name("Goblin"), Health(level * 30), Attack(level * 5) {}

void Orc::TakeDamage(int damage)
{
	Health -= damage;
}

Item* Orc::DropItem()
{
	return nullptr;
}
