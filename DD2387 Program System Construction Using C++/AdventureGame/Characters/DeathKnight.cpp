#include <iostream>
#include "DeathKnight.h"

using std::cout;

DeathKnight::DeathKnight() : Character("Deathknight") {
	int power = 50;
	_stats = {100, 70, 50, power};
	_maxWeight = power*3;
}
DeathKnight::DeathKnight(std::string str, std::string name) : Character("Deathknight", name) {
	_attackPhrase = name + ": " + str;
	int power = 50;
	_stats = {100, 100, 70, 50, power};
	_maxWeight = power*3;
}
DeathKnight::~DeathKnight() {
}
float DeathKnight::weakness(Character& src) {
	float modifier = 1;
	if(src.getStats().height > getStats().height) {
		modifier = 0.3;
	}

	return modifier;
}
std::vector<Equipment> DeathKnight::weapons() {
	Equipment twohsword("Two-handed broadsword", "BFS", 20, 20, 25);
	Equipment two1hsword("Two one-handed swords", "Slice dat shit", 15, 15, 27);
	return {twohsword, two1hsword};
}

void DeathKnight::attack(Character & ch) {
	using namespace std;

	cout << "Choose your action: (1)Melee attack, (2)Death Coil, (3)Blood Boil" << endl;
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
			damage = 0.5*(getStats().strength * modifier) * (rand() % 2 + 1);
			ch.damageChar(damage);
			cout << this->_name << "'s Death Coil did " << damage << " damage to " << ch._name << " who is now at " << ch.getStats().hp << "." << endl;
			break;
		case 3:
			damage = 0.5*(getStats().strength * modifier) * (rand() % 2 + 1);
			ch.damageChar(damage);
			cout << this->_name << "'s Blood Boil did " << damage << " damage to " << ch._name << " who is now at " << ch.getStats().hp << "." << endl;
			break;
		default:
			cout << "Invalid input" << endl;
	}



}


