//
// Created by Victor Navarro on 15/02/24.
//

#include "Character.h"
#include <string>
#include <cstring>

Character::Character(const char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer) {
    strncpy(name, reinterpret_cast<const char *>(_name), sizeof(name));
    name[sizeof(name) - 1] = '\0';
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
}

const char* Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}

int Character::getAttack() {
    return attack;
}

int Character::getDefense() {
    return defense;
}

int Character::getSpeed() {
    return speed;
}

const char* Character::toString() {
    static char buffer[300];
    sprintf(buffer, "Name: %s\nHealth: %d\nAttack: %d\nDefense: %d\nSpeed: %d", name, health, attack, defense, speed);
    return buffer;
}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::flee(Character*target) {
    if(this->speed > target->speed)
        return true;

    int chance = rand() % 100;
    return chance > 30;
}