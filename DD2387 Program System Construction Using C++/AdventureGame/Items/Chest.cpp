#include <iostream>
#include "Chest.h"

using std::cout;

Chest::Chest(std::string name, std::string description, Item* item) {
	this->_name = name;
	this->_description = description;
	this->_weight = 40;
	this->_containedItem = item;
}
Chest::~Chest() {
}
std::string Chest::use(Character *src) {
	src->addItem(_containedItem);
	return "Chest granted you a " + _containedItem->_description;
}
