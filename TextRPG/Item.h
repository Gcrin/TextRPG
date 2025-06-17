#pragma once
#include <memory>
#include <string>

class Character;

class Item
{
public:
    Item(std::string name, int price) : name(std::move(name)), price(price) {}
    virtual ~Item() = default;

    std::string getName() const { return name; }
    int getPrice() const { return price; }
    
    virtual void use(Character& character) = 0;
    virtual std::unique_ptr<Item> clone() const = 0;
protected:
    std::string name;
    int price;
};
