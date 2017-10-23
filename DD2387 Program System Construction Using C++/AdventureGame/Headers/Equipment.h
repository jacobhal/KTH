//
// Created by Adrian on 2016-06-08.
//

#ifndef CPPLAB3_EQUIPMENT_H
#define CPPLAB3_EQUIPMENT_H

#include "Item.h"
#include "Character.h"

class Equipment : public Item {
public:
    int _hpMod;
    int _strMod;

    Equipment(std::string name, std::string desc, int weight, int stam, int str);
    virtual ~Equipment();

    std::string use(Character *src){ return ""; }


};

#endif //CPPLAB3_EQUIPMENT_H
