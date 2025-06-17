#pragma once
#include "Item.h"

class AttackBoost : public Item
{
public:
    AttackBoost() : Item("공격력 강화", 15), attackIncrease(10)
    {
    }

    void use(Character& character) override;

    std::unique_ptr<Item> clone() const override
    {
        return std::make_unique<AttackBoost>(*this);
    }

private:
    int attackIncrease;
};
