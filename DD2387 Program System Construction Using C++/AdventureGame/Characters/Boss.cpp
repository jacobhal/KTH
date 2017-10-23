//
// Created by Adrian on 2016-06-08.
//
#include "Boss.h"

Boss::Boss(std::string name, std::string vl, std::string vld) : Character("Boss", name, vl){
    _voiceLineDeath = name + ": " + vld;
    _stats.hp       = 200;
    _stats.maxhp    = 200;
    _stats.strength = 30;
}

Boss::~Boss() {

}

void Boss::death() {
    std::cout << getVoiceLineDeath() << std::endl;
    dropItems();
}

void Boss::attack(Character & ch) {
    float modifier = weakness(ch);
    int damage = 0.5*(getStats().strength * modifier) * (rand() % 2 + 1);
    ch.damageChar(damage);
    std::cout << this->_name << " did " << damage << " damage to " << ch._name << " who is now at " << ch.getStats().hp << "." << std::endl;
}

float Boss::weakness(Character &src) {
    return 1;
}

std::vector<Equipment> Boss::weapons() {

}

