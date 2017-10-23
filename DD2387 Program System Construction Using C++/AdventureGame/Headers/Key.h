//
// Created by Jacob Hallman on 05/06/16.
//

#ifndef ADVENTUREGAME_KEY_H
#define ADVENTUREGAME_KEY_H

#include "Useable.h"

class Key : public Useable {
public:
    Key(std::string name, std::string description);
    ~Key();
    std::string use(Character*);
};

#endif //ADVENTUREGAME_KEY_H
