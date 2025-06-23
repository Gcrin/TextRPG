#pragma once
#include <string>
class Character;

class Item {
public:
    virtual std::string getName() const = 0;
    virtual void use(Character* character) = 0;
    virtual ~Item() = default;
};

class HealthPotion : public Item {
public:
    std::string getName() const override;
    void use(Character* character) override;
};

class AttackBoost : public Item {
public:
    std::string getName() const override;
    void use(Character* character) override;
};