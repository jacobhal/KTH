//
// Created by Adrian on 2016-06-08.
//

#include "Equipment.h"

Equipment::Equipment(std::string name, std::string desc, int weight, int stam, int str) {
    _name           = name;
    _description    = desc;
    _weight         = weight;
    _hpMod          = stam;
    _strMod         = str;
    _isEquippable   = true;
}

Equipment::~Equipment() {

}


