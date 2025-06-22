#ifndef SHOP_H
#define SHOP_H

#include "Character.h"
#include <memory>
using namespace std;

class Shop {
private:
    int visitCounter = 0;
public:
    bool shouldOpen();
    void incrementCounter();
    void open(Character* player);
};

#endif