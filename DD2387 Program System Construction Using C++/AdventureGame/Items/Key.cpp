#include <iostream>
#include "Key.h"
#include "Character.h"

using std::cout;

Key::Key(std::string name, std::string description) {
	this->_name = name;
	this->_description = description;
	this->_weight = 40;
}
Key::~Key() {
}
std::string Key::use(Character *c) {
	if(c->_location->_isLocked[c->_settingPosition-1] == 1) {
		c->_location->_isLocked[c->_settingPosition-1] = 0;
		c->removeItem(this);
		return "Unlocked door.";
	} else {
		return "No door to unlock.";
	}

}