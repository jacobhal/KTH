#include <iostream>
#include "Mage.h"

using std::cout;

Mage::Mage() : Character("Mage") {
	int power = 20;
	_stats = {100, 70, 50, power};
	_maxWeight = power*3;
}
Mage::Mage(std::string str, std::string name) : Character("Mage", name) {
	_attackPhrase = name + ": " + str;
	int power = 20;
	_stats = {100, 100, 70, 50, power};
	_maxWeight = power*3;
}
Mage::~Mage() {
}
float Mage::weakness(Character& src) {
	float modifier = 1;
	if(src.getClass() == "mage") {
		modifier = 0.3;
	}

	return modifier;
}
std::vector<Equipment> Mage::weapons() {
	Equipment staff("Staff", "A basic staff", 10, 20, 10);
	Equipment daggeroh("One-handed dagger and off-hand", "A shitty dagger and some off-hand", 10, 10, 15);
	Equipment swordoh("One-handed sword and off-hand", "Bad lowbie sword and off-hand", 15, 8, 17);
	return {staff, daggeroh, swordoh};
}

