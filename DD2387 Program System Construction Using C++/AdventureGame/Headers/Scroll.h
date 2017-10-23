//
// Created by Jacob Hallman on 05/06/16.
//

#ifndef ADVENTUREGAME_SCROLL_H
#define ADVENTUREGAME_SCROLL_H

#include "Useable.h"

class Scroll : public Useable {
public:
    Scroll(std::string name, std::string description);
    ~Scroll();
    std::string use(Character*);
};

#endif //ADVENTUREGAME_SCROLL_H
