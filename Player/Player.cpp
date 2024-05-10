//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>
#include "../Files/FileHandler.h"

using namespace std;

void Player::SaveProgress(){
    char* buffer = this->serialize();
    FileHandler fileHandler = FileHandler();

    fileHandler.writeToFile("PlayerInfo.data", buffer, Player::BUFFER_SIZE);
}

Player::Player(const char* _name, int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}

Player::Player(const char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer, int _level, int _experience): Character(_name, _health, _attack, _defense, _speed, _isPlayer){
    level = _level;
    experience = _experience;
}


void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;

    health-= trueDamage;

    cout << name << " took " << trueDamage << " damage!" << endl;

    if(health <= 0) {
        cout << name << " has been defeated!" << endl;
    }
}

void Player::levelUp() {
    level++;
    //Incrementar las estadisticas al subir de nivel
    health += 6;
    attack += 3;
    defense += 1;
    speed += 3;

    cout<<"¡You've reached level "<<level<<"!"<<endl;
    cout<<"¡Your stats are:"<<endl;
    cout<<"Health: "<< health <<endl;
    cout<<"Attack: "<< attack <<endl;
    cout<<"Defense: "<< defense <<endl;
    cout<<"Speed: "<< speed <<endl;
}

void Player::gainExperience(Enemy* enemies) {
    int exp = enemies->getExperience();
    experience += exp;
    while(experience>=100){
        int RestoExp = experience - 100;
        levelUp();
        experience = RestoExp;
    }
    cout << "Current experience: " << experience << endl;
}

void Player::defend() {
    DefenseBase = defense;
    defense += defense * 0.2;
    cout << name << " is defending!" << endl;
    defense = DefenseBase;
}

void Player::resetDefense(){
    defense = DefenseBase;
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Select a target: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(vector<Enemy*> enemies) {
    int action = 0;
    cout << "Select an action: " << endl
         << "1. Attack" << endl
         << "2. Defend" << endl
         << "3. Save Player Progress" << endl;

    cin >> action;
    Action currentAction;
    Character* target = nullptr;

    switch(action) {
        case 1:
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target](){
                doAttack(target);
            };
            currentAction.speed = getSpeed();
            break;
        case 2:
            currentAction.action = [this](){
                defend();
            };
            currentAction.speed = getSpeed();
            break;
        case 3:
            SaveProgress();
            return takeAction(enemies);
            break;
        default:
            cout << "Invalid action" << endl;
            return takeAction(enemies);
            break;
    }

    return currentAction;
}
//Serialización: Arreglo donde cada elemento mida un char (1 byte)
//Iterador: Puntero que se mueve a traves del buffer
//Buffer: Arreglo
char* Player::serialize() {
    char* iterator = buffer;

    memcpy(iterator, &name, sizeof(name));
    iterator += sizeof(name);

    memcpy(iterator, &health, sizeof(health));
    iterator += sizeof(health);

    memcpy(iterator, &attack, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(iterator, &defense, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(iterator, &speed, sizeof(speed));
    iterator += sizeof(speed);

    memcpy(iterator, &isPlayer, sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(iterator, &level, sizeof(level));
    iterator += sizeof(level);

    memcpy(iterator, &experience, sizeof(experience));

    return buffer;
}

//Chars array = One byte for element
Player* Player::unserialize(char *buffer) {
    char* iterator = buffer;
    char name[50];
    int health, attack, defense, speed, level, experience;
    bool isPlayer;

    memcpy(&name, iterator, sizeof(name));
    iterator += sizeof(name);

    memcpy(&health, iterator, sizeof(health));
    iterator += sizeof(health);

    memcpy(&attack, iterator, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(&defense, iterator, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(&speed, iterator, sizeof(speed));
    iterator += sizeof(speed);

    memcpy(&isPlayer, iterator, sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(&level, iterator, sizeof(level));
    iterator += sizeof(level);

    memcpy(&experience, iterator, sizeof(experience));
    iterator += sizeof(experience);

    return new Player(name, health, attack, defense, speed, isPlayer, level, experience);

}