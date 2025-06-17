#include "Monster.h"
#include "AttackBoost.h"
#include "HealthPotion.h"

Monster::Monster(std::string name, int health, int attack) : name(std::move(name)), currentHealth(health),
                                                             attack(attack)
{
}

void Monster::takeDamage(int damage)
{
    currentHealth -= damage;
    currentHealth = std::max(currentHealth, 0);
}

std::unique_ptr<Item> Monster::dropItem()
{
    if (Utils::getRandomInt(1, 100) <= 30)
    {
        if (Utils::getRandomInt(0, 1) == 0)
        {
            return std::make_unique<HealthPotion>();
        }
        return std::make_unique<AttackBoost>();
    }
    return nullptr;
}
