#include <iostream>
#include "Scroll.h"
#include "Character.h"

using std::cout;

Scroll::Scroll(std::string name, std::string description) {
	this->_name = name;
	this->_description = description;
	this->_weight = 40;
}
Scroll::~Scroll() {
}
std::string Scroll::use(Character* c) {
	c->_stats.hp += 20;
	c->_stats.maxhp += 20;
	c->_stats.strength += 20;
	c->removeItem(this);
	return "All stats increased by 20.";
}
