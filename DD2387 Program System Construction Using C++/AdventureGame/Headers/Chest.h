//
// Created by Jacob Hallman on 05/06/16.
//

#ifndef ADVENTUREGAME_CHEST_H
#define ADVENTUREGAME_CHEST_H

#include "Container.h"

class Chest : public Container {
public:
    Chest(std::string name, std::string description, Item* item);
    ~Chest();
    std::string use(Character *src);
};

#endif //ADVENTUREGAME_CHEST_H
