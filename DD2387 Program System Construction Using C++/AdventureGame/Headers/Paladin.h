//
// Created by Jacob Hallman on 05/06/16.
//

#ifndef ADVENTUREGAME_PALADIN_H
#define ADVENTUREGAME_PALADIN_H

#include "Character.h"

class Paladin : public Character {

public:
    Paladin();
    Paladin(std::string, std::string);
    ~Paladin();
    float weakness(Character& src);
    std::vector<Equipment> weapons();
    void attack(Character & ch);
};

#endif //ADVENTUREGAME_PALADIN_H
