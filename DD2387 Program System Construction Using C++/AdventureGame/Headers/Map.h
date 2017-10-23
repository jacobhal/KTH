//
// Created by Jacob Hallman on 05/06/16.
//

#ifndef ADVENTUREGAME_MAP_H
#define ADVENTUREGAME_MAP_H

#include "Useable.h"

class Map : public Useable {
public:
    Map(std::string name, std::string description);
    ~Map();
    std::string use(Character*);
};

#endif //ADVENTUREGAME_MAP_H
