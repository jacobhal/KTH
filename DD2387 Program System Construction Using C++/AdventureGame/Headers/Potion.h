//
// Created by Jacob Hallman on 07/06/16.
//

#ifndef ADVENTUREGAME_POTION_H
#define ADVENTUREGAME_POTION_H

#include "Useable.h"

class Potion : public Useable {
public:
    Potion(std::string name, std::string description);
    ~Potion();
    std::string use(Character*);
};

#endif //ADVENTUREGAME_POTION_H
