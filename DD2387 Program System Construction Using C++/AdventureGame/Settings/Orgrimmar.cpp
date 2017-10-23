#include <iostream>
#include "Orgrimmar.h"

Orgrimmar::Orgrimmar(std::string name, std::string description) {
	this->_name = name;
	this->_description = description;
	this->_isLocked = {0,0,0,0};
}
Orgrimmar::~Orgrimmar() {
}