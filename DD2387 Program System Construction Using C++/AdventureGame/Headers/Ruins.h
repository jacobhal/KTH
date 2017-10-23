//
// Created by Jacob Hallman on 05/06/16.
//

#ifndef ADVENTUREGAME_RUINS_H
#define ADVENTUREGAME_RUINS_H

#include "Inside.h"

class Ruins : public Inside {

public:
    Ruins(std::string name, std::string description);
    ~Ruins();
};

#endif //ADVENTUREGAME_RUINS_H
