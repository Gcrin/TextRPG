#pragma once
#include "Item.h"

class HealthPotion : public Item
{
public:
    HealthPotion() : Item("Health Potion", 10), healthRestore(50)
    {
    }

    void use(Character& character) override;

    std::unique_ptr<Item> clone() const override
    {
        return std::make_unique<HealthPotion>(*this);
    }

private:
    int healthRestore;
};