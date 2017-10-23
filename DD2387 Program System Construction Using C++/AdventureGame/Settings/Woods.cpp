#include <iostream>
#include "Woods.h"

Woods::Woods(std::string name, std::string description) {
	this->_name = name;
	this->_description = description;
	this->_isLocked = {0,0,0,0};
}
Woods::~Woods() {
}