#include <iostream>
#include "Map.h"
#include "Character.h"

using std::cout;

Map::Map(std::string name, std::string description) {
	this->_name = name;
	this->_description = description;
	this->_weight = 40;
}
Map::~Map() {
}
std::string Map::use(Character* c) {
	cout << "Current position \n";
	cout << c->_location->_description << "\n";
	cout << "Available directions \n";
	for(auto elem : c->_location->getRoutes()) {
		cout << elem << "\n";
	}
	return "";
}
