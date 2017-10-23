#ifndef _ITEM_H
#define _ITEM_H
#include <string>
#include <vector>
#include <iostream>

class Character;

class Item {
public:
	virtual ~Item() {};
	std::string _name;
	std::string _description;
	int _settingPosition;
	int _weight;
	bool _isEquippable = false;
	friend bool operator== (const Item &i1, const Item &i2) { return i1._name == i2._name; }

	virtual std::string use(Character *src) =0;

	friend std::ostream& operator<<(std::ostream& os, const Item& it) {
		os << it._name << ": " << it._description;
		return os;
	}
};
#endif