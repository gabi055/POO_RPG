//
// Created by Victor Navarro on 15/02/24.
//

#include "Character.h"
#include <string>
#include <cstring>
#include <iostream>

Character::Character(const char* _name, int _health, int _maxHealth, int _attack, int _defense, int _speed, bool _isPlayer) {
    strcpy(name, _name);
    health = _health;
    maxHealth = _maxHealth;
    attack = _attack;
    defense = _defense;
    defenseBase = _defense;
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

void Character::defend() {
    defense += defense * 0.2;
    cout << name << " is defending!" << endl;
}

void Character::resetDefense(){
    defense = defenseBase;
}

const char* Character::toString() {
    static char buffer[300];
    sprintf(buffer, "Name: %s\nHealth: %d\nMax Health: %d\nAttack: %d\nDefense: %d\nDefense Base: %d\nSpeed: %d", name, health, maxHealth, attack, defense, defenseBase, speed);
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