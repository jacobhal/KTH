//
// Created by Jacob Hallman on 05/06/16.
//

#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include "Item.h"
#include "Character.h"
#include "Setting.h"


Setting::Setting() {
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    int month = (now->tm_mon);
    if(month > 0 && month <= 3) {
        _season = "Spring";
    } else if(month > 3 && month <= 6) {
        _season = "Summer";
    } else if(month > 6 && month <= 9) {
        _season = "Autumn";
    } else if(month > 9 && month <= 12) {
        _season = "Winter";
    }
}

Setting::~Setting() {}; // Even pure virtual destructors must be defined

float Setting::current_time() {
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    float c_time = ((float)(now->tm_hour) * 100 + (float)(now->tm_min)) / 100;
    return c_time;
};
// Item methods
// TODO Fixa
bool Setting::hasItem(std::string name) {
    for(int i = 0; i < _items.size(); ++i) {
        if(_items[i]->_name == name)
            return true;
    }
    return false;
}
bool Setting::hasItem(int position) {
    for(int i = 0; i < _items.size(); ++i) {
        if(_items[i]->_settingPosition == position)
            return true;
    }
    return false;
}
std::vector<Item*> Setting::getItemByPosition(int position) {
    std::vector<Item*> iv;
    for(Item* i : _items) {
        if(i->_settingPosition == position) {
            iv.push_back(i);
        }
    }
    return iv;

}
Item* Setting::getItemByName(std::string name) {
    auto it = std::find_if(_items.begin(), _items.end(), [&name] (const Item* p) -> bool { return p->_name == name; });

    if(it != _items.end()) {
        return *it;
    } else {
        return nullptr;
    }
}
void Setting::addItem(Item *item, int position) {
    if(!hasItem(item->_name)) {
        item->_settingPosition = position;
        _items.push_back(item);
    }
};
void Setting::removeItem(Item *item){
    _items.erase(std::remove(_items.begin(), _items.end(), item), _items.end());
};
// Route methods
void Setting::addRoute(Setting *setting, std::string keyword) {
    _routes.push_back(std::make_pair(setting, keyword));
}
void Setting::removeRoute(Setting *setting, std::string keyword) {
    _routes.erase(std::remove(_routes.begin(), _routes.end(), std::make_pair(setting, keyword)), _routes.end());
}
Setting* Setting::hasRoute(std::string keyword) {
    // Use lambda function
    auto it = std::find_if(_routes.begin(), _routes.end(), [&keyword] (const std::pair<Setting*, std::string> & p) -> bool { return p.second == keyword; });

    if(it != _routes.end()) {
        return it->first;
    } else {
        return NULL;
    }
}
Setting* Setting::move(Character* character, std::string keyword) {
    auto it = hasRoute(keyword);
    if(it != NULL) {
        character->_location = it;
        return it;
    }
    return NULL;
}
std::vector<std::string> Setting::getRoutes() const {
    std::vector<std::string> v;
    for(auto pair: _routes) {
        v.push_back(pair.second);
    }
    return v;
}

void Setting::lockRoute(int i) {
    this->_isLocked[i-1] = 1;
}

void Setting::unlockRoute(int i) {
    this->_isLocked[i-1] = 0;
}

// Character methods
void Setting::addCharacter(Character *character, int position) {
    character->_settingPosition = position;
    character->_location = this;
    _characters.push_back(character);
}
void Setting::removeCharacter(Character *character) {
    _characters.erase(std::remove(_characters.begin(), _characters.end(), character), _characters.end());
}
bool Setting::hasCharacter(int position) {
    for(int i = 0; i < _characters.size(); ++i) {
        if(_characters[i]->_settingPosition == position)
            return true;
    }
    return false;
}

bool Setting::hasCharacter(std::string name) {
    for(int i = 0; i < _characters.size(); ++i) {
        if(_characters[i]->_name == name)
            return true;
    }
    return false;
}

Character* Setting::getCharacterByPosition(int position) {
    auto it = std::find_if(_characters.begin(), _characters.end(), [&position] (const Character* p) -> bool { return p->_settingPosition == position; });

    if(it != _characters.end()) {
        return *it;
    } else {
        return nullptr;
    }
}

Character* Setting::getCharacterByName(std::string name) {
    auto it = std::find_if(_characters.begin(), _characters.end(), [&name] (const Character* p) -> bool { return p->_name == name; });

    if(it != _characters.end()) {
        return *it;
    } else {
        return nullptr;
    }
}


