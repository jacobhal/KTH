#ifndef _CHARACTER_H
#define _CHARACTER_H
#include <string>
#include <vector>
#include <iostream>

#include "Item.h"
#include "Setting.h"
#include "Useable.h"
#include "Container.h"
#include "Equipment.h"

class Setting;
class Useable;
class Container;
class Equipment;

struct Stats {
	int maxhp;
	int hp;
	int weight;
	int height;
	int strength;
};

class Character {
public:
	
	Setting*                    _location;
    std::vector<Item*>          _inventory;
	Stats 						_stats;
	std::string					_attackPhrase;
	int 						_maxWeight;
	int 						_settingPosition;
	std::string					_voiceLine;
	std::string 				_name;
	Equipment*					_weapon;
	bool 						_stateChanged = 0;

	virtual ~Character(); // Even pure virtual destructors must be defined

	std::string getClass() {
		return _class;
	}

	Stats getStats() {
		return _stats;
	}




	// Item methods
	/*
	bool hasItem(std::string name) const {
		if(std::find(inventory.begin(), inventory.end(), [&name] (const Item* p) -> bool { return p->name == name; })){
	    	return true;
		} else {
		 	return false;
		}
	};
	*/
	bool hasItem(std::string name) const;
	void addItem(Item *item);
	void removeItem(Item *item);
	void useItem(Useable *item);
	void openItem(Container *item);
	void equipItem(Equipment *item);
	// TODO Fixa
	Item* getItemByName(std::string n);
    void dropItems();

	// Setting methods
	Setting* currentArea() const;
	void setLocation(Setting & setting);

	// Character methods
	std::string talkTo(Character & ch) const;
	void damageChar(int dmg);
	void healChar(int hp);
	virtual void attack(Character & ch);
	int fight(Character & ch);
	virtual void death(){};

	virtual std::vector<Equipment> weapons() =0;

	virtual float weakness(Character& src) =0; // Define the certain threats to a given class
protected:
	Character(std::string s, std::string s2 = "noname", std::string s3 = "*shrug*") : _class(s), _name(s2), _voiceLine(s3), _attackPhrase(s2 + ": " + s3) {};
private:
    const std::string _class;

};
#endif