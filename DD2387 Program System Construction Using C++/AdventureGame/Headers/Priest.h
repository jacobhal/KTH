//
// Created by Jacob Hallman on 05/06/16.
//

#ifndef ADVENTUREGAME_PRIEST_H
#define ADVENTUREGAME_PRIEST_H

#include "Character.h"

class Priest : public Character {

public:
    Priest();
    Priest(std::string str, std::string);
    ~Priest();
    float weakness(Character& src);
    std::vector<Equipment> weapons();
    void attack(Character & ch);

};

#endif //ADVENTUREGAME_PRIEST_H
