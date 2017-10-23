#include <iostream>
#include "Priest.h"

using std::cout;

Priest::Priest() : Character("Priest") {
	int power = 30;
	_stats = {100, 50, 50, power};
	_maxWeight = power*3;
}
Priest::Priest(std::string str, std::string name) : Character("Priest", name) {
	_attackPhrase = name + ": " + str;
	int power = 30;
	_stats = {100, 100, 50, 50, power};
	_maxWeight = power*3;
}
Priest::~Priest() {
}
float Priest::weakness(Character& src) {
	float modifier = 1;
	if(src.getClass() == "mage") {
		modifier = 0.3;
	}

	return modifier;
}
std::vector<Equipment> Priest::weapons() {
	Equipment staff("Staff", "A basic staff", 10, 20, 10);
	Equipment daggeroh("One-handed dagger and off-hand", "A shitty dagger and some off-hand", 10, 10, 15);
	return {staff, daggeroh};
}

void Priest::attack(Character & ch) {
	using namespace std;

	cout << "Choose your action: (1)Wand Attack, (2)Smite, (3)Flash Heal" << endl;
	int action;
	cin >> action;

	float modifier = weakness(ch);
	int damage;
	switch(action) {
		case 1:
			damage = 0.5*(getStats().strength * modifier) * (rand() % 2 + 1);
			ch.damageChar(damage);
			cout << this->_name << "'s wand attack did " << damage << " damage to " << ch._name << " who is now at " << ch.getStats().hp << "." << endl;
			break;
		case 2:
			damage = 0.5*(getStats().strength * modifier) * (rand() % 2 + 1);
			ch.damageChar(damage);
			cout << this->_name << "'s Smite did " << damage << " damage to " << ch._name << " who is now at " << ch.getStats().hp << "." << endl;
			break;
		case 3:
			healChar(30);
			cout << this->_name << " healed for 30" << "." << endl;
			break;
		default:
			cout << "Invalid input" << endl;
	}
}
