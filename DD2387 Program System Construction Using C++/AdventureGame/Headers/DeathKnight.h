//
// Created by Jacob Hallman on 05/06/16.
//

#ifndef ADVENTUREGAME_DEATHKNIGHT_H
#define ADVENTUREGAME_DEATHKNIGHT_H

#include "Character.h"

class DeathKnight : public Character {

public:
    DeathKnight();
    DeathKnight(std::string str, std::string);
    ~DeathKnight();
    float weakness(Character& src);
    std::vector<Equipment> weapons();
    void attack(Character & ch);
};

#endif //ADVENTUREGAME_DEATHKNIGHT_H
