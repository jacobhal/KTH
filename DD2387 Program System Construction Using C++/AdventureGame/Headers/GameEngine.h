#ifndef _GAMEENGINE_H
#define _GAMEENGINE_H
#include <string>
#include <vector>
#include <map>

class Setting;
class Character;
class Item;

class GameEngine {

private:
	std::vector<std::string> 				_availableCommands;
	std::map<std::string, std::string> 		_descriptions;
	Setting*								_currentSetting;
	Character*								_player;
	std::vector<Item*> 				_items;
	std::map<std::string, int> 				_lookup;
	bool _isRunning;
	
	void userCommand(std::string command, bool hasOption);
    void help();
    Item* getItemByName(std::string name);

public:
	GameEngine(Setting *setting, Character *player, std::vector<Item*> items);
	~GameEngine() {}; // Even pure virtual destructors must be defined

	void init();
	void run();

};
#endif