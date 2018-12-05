//
// Created by CalPC on 12/3/2018.
//

#ifndef BORK_DISHES_H
#define BORK_DISHES_H
#include "Item.h"

class Dishes : public Item {
public:
    Dishes();
    void useItem();
private:
    bool isClean = false;
};


#endif //BORK_DISHES_H
