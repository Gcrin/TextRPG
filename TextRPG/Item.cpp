#include "Item.h"
#include "Character.h"

std::string HealthPotion::getName() const { return "Health Potion"; }
void HealthPotion::use(Character* character) { character->heal(50); }

std::string AttackBoost::getName() const { return "Attack Boost"; }
void AttackBoost::use(Character* character) { character->increaseAttack(10); }