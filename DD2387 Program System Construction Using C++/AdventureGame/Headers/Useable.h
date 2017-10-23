//
// Created by Jacob Hallman on 07/06/16.
//

#ifndef ADVENTUREGAME_USEABLE_H
#define ADVENTUREGAME_USEABLE_H

#include "Item.h"
#include "Character.h"

class Character;

class Useable : public Item {
public:
    std::string use(Character*){ return ""; }
};

#endif //ADVENTUREGAME_USEABLE_H
