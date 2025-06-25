#include "Monster.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "Utils.h"

Monster::Monster(std::string name, int playerLevel, float healthMultiplier, float attackMultiplier)
    : name(std::move(name)),
      currentHealth(Utils::getRandomInt(
          static_cast<int>(playerLevel * 20 * healthMultiplier),
          static_cast<int>(playerLevel * 30 * healthMultiplier)
      )),
      attack(Utils::getRandomInt(
          static_cast<int>(playerLevel * 5 * attackMultiplier),
          static_cast<int>(playerLevel * 10 * attackMultiplier)
      ))
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
