#include <iostream>
#include "Ruins.h"

Ruins::Ruins(std::string name, std::string description) {
	this->_name = name;
	this->_description = description;
	this->_isLocked = {0,0,0,0};
}
Ruins::~Ruins() {
}