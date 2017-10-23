//
// Created by Jacob Hallman on 05/06/16.
//

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Item.h"
#include "Setting.h"
#include "Character.h"

class Setting;

Character::~Character() {}; // Even pure virtual destructors must be defined


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
bool Character::hasItem(std::string name) const{
    for(int i = 0; i < _inventory.size(); ++i) {
        if(_inventory[i]->_name == name)
            return true;
    }
    return false;
}
void Character::addItem(Item *item) {
    if(!hasItem(item->_name)) {
        _inventory.push_back(item);
    }
}
void Character::removeItem(Item *item){
    _inventory.erase(std::remove(_inventory.begin(), _inventory.end(), item), _inventory.end());
}
// TODO Fixa
Item* Character::getItemByName(std::string n) {
        auto it = std::find_if(_inventory.begin(), _inventory.end(),
                               [&n](const Item *p) -> bool { return p->_name == n; });

        if (it != _inventory.end()) {
            return *it;
        } else {
            return nullptr;
        }
}

void Character::useItem(Useable *item) {
    // TODO: Check that player has item and add functionality in item files
    if(hasItem(item->_name)) {
        std::cout << item->use(this) << std::endl;
    }
}

void Character::openItem(Container *item) {
    // TODO: Check that player has item and add functionality in item files
    if(hasItem(item->_name)) {
        std::cout << item->use(this) << std::endl;
        removeItem(item);
    }
}

void Character::equipItem(Equipment *item) {
    if(_weapon != nullptr) {
        // Remove stat modifiers and place current weapon in backpack
        _stats.hp -= _weapon->_hpMod;
        _stats.maxhp    -= _weapon->_hpMod;
        _stats.strength -= _weapon->_strMod;
        this->addItem(_weapon);
    }

    // Add new weapon to weapon slot
    _weapon          = item;
    _stats.hp       += item->_hpMod;
    _stats.maxhp    += _weapon->_hpMod;
    _stats.strength += item->_strMod;
    this->removeItem(item);

    std::cout << "Equipped " + _weapon->_name << "." << std::endl;

}

void Character::dropItems() {
    if (_inventory.size() > 0) {
        std::cout << _name << " dropped:" << std::endl;

        for (int i = 0; i < _inventory.size(); ++i) {
            _location->addItem(_inventory[i], _settingPosition);
            std::cout << _inventory[i]->_name << std::endl;
        }
    }
}

// Setting methods
Setting* Character::currentArea() const {
    return _location;
}
void Character::setLocation(Setting & setting) {
    _location = &setting;
}

// Character methods
std::string Character::talkTo(Character & ch) const{
    return ch._voiceLine;
}

void Character::damageChar(int dmg) {
    getStats().hp - dmg < 0 ? _stats.hp = 0 : _stats.hp -= dmg;
}

void Character::healChar(int hp) {
    getStats().hp + hp > 100 ? _stats.hp = 100 : _stats.hp += hp;
}

// Default attack (this will be different for each playable class and also provide options
void Character::attack(Character & ch) {
    float modifier = weakness(ch);
    int damage = 0.5*(getStats().strength * modifier) * (rand() % 2 + 1);
    ch.getStats().hp - damage < 0 ? ch._stats.hp = 0 : ch._stats.hp -= damage;
    std::cout << this->_name + " did " + std::to_string(damage) + " damage to " + ch._name + " who is now at " + std::to_string(ch.getStats().hp) + "." << std::endl;
}

int Character::fight(Character & ch) {
    std::cout << "--Entering battle with " << ch._name << "--" << std::endl;
    while(1) {
        if(this->getStats().hp <= 0) {
            continue;
        }

        std::cout << "Choose your action: (1)attack, (2)flee";
        if(hasItem("potion")){
            std::cout << ", (3)use potion[heal for 50hp]";
        }
        std::cout << std::endl;
        int c;
        std::cin >> c;
        switch(c) {
            case 1:
                attack(ch);
                if (ch.getStats().hp <= 0) {
                    ch.death();
                    _location->removeCharacter(&ch);
                    std::cout << "You defeated " << ch._name << "." << std::endl;
                    if(ch._name == "Shrek") {
                        ch._location->getCharacterByName("Jaina")->_attackPhrase = "Jaina: Well done, hero. Your reward is a scroll which can increase your powers.";
                        ch._location->getCharacterByName("Jaina")->_stateChanged = 1;
                    }
                    return 1;
                } else {
                    ch.attack(*this);
                    if (getStats().hp <= 0) {
                        std::cout << "You died." << std::endl;
                        return -1;
                    }
                }
                break;
            case 2:
                std::cout << "You fled from " << ch._name << "." << std::endl;
                return 0;
            case 3:
                if (hasItem("potion")) {
                    this->useItem(dynamic_cast<Useable *>(getItemByName("potion")));
                }
                break;
            default:
                std::cout << "Not a valid option!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

}



