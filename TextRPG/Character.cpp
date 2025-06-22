#include "Character.h"
#include "Item.h"
#include <iostream>
#include <algorithm>
using namespace std;

Character::Character(const string& name) : name(name) {}

string Character::getName() const { return name; }

int Character::getLevel() const { return level; }
int Character::getHealth() const { return health; }
int Character::getAttack() const { return attack; }
int Character::getGold() const { return gold; }

void Character::heal(int amount) { health = min(maxHealth, health + amount); }
void Character::increaseAttack(int amount) { attack += amount; }
void Character::takeDamage(int damage) { health -= damage; if (health < 0) health = 0; }

bool Character::isAlive() const { return health > 0; }

void Character::gainExperience(int exp) 
{
    experience += exp;
    while (experience >= 100 && level < 10) {
        experience -= 100;
        level++;
        attack += level * 5;
        maxHealth += level * 20;
        health = maxHealth;
        cout << "\n[������!] Lv." << level << " ü�°� ���ݷ� ����!\n";
    }
}

void Character::gainGold(int amount) 
{
    gold += amount;
}

void Character::addItem(unique_ptr<Item> item) 
{
    inventory.push_back(move(item));
}

void Character::useRandomItem() 
{
    if (inventory.empty()) return;
    int index = rand() % inventory.size();
    cout << "\n[������ ���!] " << inventory[index]->getName() << endl;
    inventory[index]->use(this);
    inventory.erase(inventory.begin() + index);
}

void Character::displayStatus() const 
{
    cout << "\n[���� ����] " << name << " | Lv." << level << " | HP: " << health << "/" << maxHealth << " | ATK: " << attack << " | Gold: " << gold << "\n";
}

void Character::showInventory() const 
{
    if (inventory.empty()) 
    {
        cout << "�κ��丮�� ��� �ֽ��ϴ�.\n";
        return;
    }
    for (size_t i = 0; i < inventory.size(); ++i) 
    {
        cout << i + 1 << ". " << inventory[i]->getName() << "\n";
    }
}

bool Character::sellItem(int index, int& goldEarned) {
    if (index < 0 || index >= inventory.size()) return false;

    string name = inventory[index]->getName();

    if (name == "Health Potion") goldEarned = 6;
    else if (name == "Attack Boost") goldEarned = 9;
    else return false;

    inventory.erase(inventory.begin() + index);
    gainGold(goldEarned);

    return true;
}

int Character::getInventorySize() const {
    return inventory.size();
}