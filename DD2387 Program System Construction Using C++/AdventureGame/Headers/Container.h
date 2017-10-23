//
// Created by Jacob Hallman on 07/06/16.
//

#ifndef ADVENTUREGAME_CONTAINER_H
#define ADVENTUREGAME_CONTAINER_H

#include "Item.h"
#include "Character.h"

class Character;

class Container : public Item {
public:
    Item* _containedItem;
    std::string use(Character *src){ return ""; }
};

#endif //ADVENTUREGAME_CONTAINER_H
