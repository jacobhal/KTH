#include <iostream>
#include "Beast.h"

using std::cout;

Beast::Beast() : Character("Beast") {
	int power = 40;
	_stats = {100, 70, 50, power};
	_maxWeight = power*3;
}
Beast::Beast(std::string str, std::string name) : Character("Beast", name) {
	_attackPhrase = name + ": " + str;
	int power = 40;
	_stats = {100, 100, 70, 50, power};
	_maxWeight = power*3;
}
Beast::~Beast() {
}
float Beast::weakness(Character& src) {
	float modifier = 1;
	if(src.getClass() == "mage") {
		modifier = 0.3;
	}

	return modifier;
}
std::vector<Equipment> Beast::weapons() {
	return {};
}
