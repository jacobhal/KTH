#include <iostream>
#include "Paladin.h"

using std::cout;

Paladin::Paladin() : Character("Paladin") {
	int power = 45;
	_stats = {100, 80, 50, power};
	_maxWeight = power*3;
}
Paladin::Paladin(std::string str, std::string name) : Character("Paladin", name) {
	_attackPhrase = name + ": " + str;
	int power = 45;
	_stats = {100, 100, 80, 50, power};
	_maxWeight = power*3;
}
Paladin::~Paladin() {
}
float Paladin::weakness(Character& src) {
	float modifier = 1;
	if(src.getClass() == "mage") {
		modifier = 0.3;
	}

	return modifier;
}
std::vector<Equipment> Paladin::weapons() {
	Equipment twohmace("Two-handed mace", "A big ass 2h mace", 20, 20, 20);
	Equipment swordshield("One-handed sword and shield", "A basic sword and a shield", 18, 25, 15);
	return {twohmace, swordshield};
}

void Paladin::attack(Character & ch) {
	using namespace std;

	cout << "Attacks available: (1)Melee attack, (2)Crusader Strike, (3)Holy Strike" << endl;
	int action;
	cin >> action;

	float modifier = weakness(ch);
	int damage;
	switch(action) {
		case 1:
			damage = 0.5*(getStats().strength * modifier) * (rand() % 2 + 1);
			ch.damageChar(damage);
			cout << this->_name << "'s melee attack did " << damage << " damage to " << ch._name << " who is now at " << ch.getStats().hp << "." << endl;
			break;
		case 2:
			damage = 0.5*((getStats().strength + (getStats().hp*0.3)) * modifier) * (rand() % 2 + 1);
			ch.damageChar(damage);
			cout << this->_name << "'s Crusader Strike did " << damage << " damage to " << ch._name << " who is now at " << ch.getStats().hp << "." << endl;
			break;
		case 3:
			damage = 0.3*((getStats().strength * modifier) * (rand() % 2 + 1));
			ch.damageChar(damage);
			healChar(damage*0.5);
			cout << this->_name << "'s Holy Strike healed for " << damage*0.5 << " and did " << damage << " damage to " << ch._name << " who is now at " << ch.getStats().hp << "." << endl;
			break;
		default:
			cout << "Invalid input" << endl;
	}

}

