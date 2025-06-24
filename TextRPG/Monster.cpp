#include "Monster.h"
#include <algorithm>

Monster::Monster(std::string name, int health, int attack, int experience)
	:Name(std::move(name)), Health(health), Attack(attack), Experience(experience)
{

}

void Monster::TakeDamage(int damage)
{
	Health -= damage;
	Health = std::max(Health, 0);
}