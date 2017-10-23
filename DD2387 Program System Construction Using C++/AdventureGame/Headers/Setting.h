#ifndef _SETTING_H
#define _SETTING_H
#include <string>
#include <vector>
#include "Item.h"
#include "Character.h"

class Item;
class Character;

class Setting {
public:
	std::string 									_name;
	std::string 									_description;
	std::string 									_season;
	std::vector<Item*> 								_items;
	std::vector<std::pair<Setting*, std::string>> 	_routes;
	std::vector<Character*> 						_characters;
	std::vector<bool>								_isLocked;

	Setting();
	virtual ~Setting(); // Even pure virtual destructors must be defined

	float current_time();

	// Item methods
	bool hasItem(std::string name);
	bool hasItem(int position);
	std::vector<Item*> getItemByPosition(int position);
	Item* getItemByName(std::string name);
	void addItem(Item *item, int position);
	void removeItem(Item *item);

	// Route methods
	void addRoute(Setting *setting, std::string keyword);
	void removeRoute(Setting *setting, std::string keyword);
	Setting* hasRoute(std::string keyword);
	Setting* move(Character* character, std::string keyword);
	std::vector<std::string> getRoutes() const;
	void lockRoute(int);
	void unlockRoute(int);

	// Character methods
	void addCharacter(Character *character, int position);
	void removeCharacter(Character *character);
	bool hasCharacter(int position);
	bool hasCharacter(std::string name);
	Character* getCharacterByPosition(int position);
	Character* getCharacterByName(std::string name);
};
#endif