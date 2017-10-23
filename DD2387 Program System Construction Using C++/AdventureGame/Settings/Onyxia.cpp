//
// Created by Jacob Hallman on 08/06/16.
//

#include <iostream>
#include "Onyxia.h"

Onyxia::Onyxia(std::string name, std::string description) {
	this->_name = name;
	this->_description = description;
	this->_isLocked = {0,0,0,0};

}
Onyxia::~Onyxia() {
}


