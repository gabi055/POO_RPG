//
// Created by Victor Navarro on 15/02/24.
//

#include "Enemy.h"
#include "../Utils.h"
#include <iostream>


using namespace std;
using namespace combat_utils;

Enemy::Enemy(const char* _name, int _health, int _maxHealth, int _attack, int _defense, int _speed, int _experience, int _level) : Character(_name, _health, _maxHealth, _attack, _defense, _speed, false) {
    experience = _experience;
    level = _level;
}

void Enemy::doAttack(Character *target) {
    target->takeDamage(getRolledAttack(attack));
}

void Enemy::takeDamage(int damage) {
    int trueDamage = damage - defense;
    health-= trueDamage;

    cout << name << " took " << trueDamage << " damage!" << endl;
    if(health <= 0) {
        cout << name << " has been defeated!" << endl;
    }
}

bool Enemy::shouldDefend(){
    if(health < maxHealth * 0.15){
        int chance = rand() % 100;
        return chance < 40;
    }
    return false;
}

int Enemy::getMaxHealth(){
    return maxHealth;
}
int Enemy::getExperience() {
    return experience;
}

void Enemy::levelUp() {
    cout << "The enemy " << name <<  " has been upgraded!" << endl;
    level++;
    //Incrementar las estadisticas al subir de nivel
    health += 6;
    maxHealth += 6;
    attack += 3;
    defense += 1;
    defenseBase += 1;
    speed += 3;
}

Character* Enemy::selectTarget(vector<Player*> possibleTargets) {
    //target with less health
    int lessHealth = 9999999;
    Character* target = nullptr;
    for(auto character : possibleTargets) {
        if(character->getHealth() < lessHealth) {
            lessHealth = character->getHealth();
            target = character;
        }
    }
    return target;
}

Action Enemy::takeAction(vector<Player*> partyMembers) {
    Action currentAction;
    currentAction.speed = getSpeed();

    Character* target = selectTarget(partyMembers);
    currentAction.target = target;
    currentAction.action = [this, target](){
        doAttack(target);
    };

    return currentAction;
}