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

    cout << "\tProgress has been saved" << endl
    << "\n\tCurrent stats:" << endl
    << this->toString() << endl;
}

Player::Player(const char _name[], int _health, int _maxHealth, int _attack, int _defense, int _speed) : Character(_name, _health, _maxHealth, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}

Player::Player(const char* _name, int _health, int _maxHealth, int _attack, int _defense, int _speed, bool _isPlayer, int _level, int _experience): Character(_name, _health, _maxHealth, _attack, _defense, _speed, _isPlayer){
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
    maxHealth += 6;
    attack += 3;
    defense += 1;
    defenseBase += 1;
    speed += 3;

    cout<<"\t¡You've reached level "<<level<<"!"<<endl;
    cout<<"\t¡Your stats are:"<<endl;
    cout<<"\tHealth: "<< health <<endl;
    cout<<"\tMax Health: "<< maxHealth <<endl;
    cout<<"\tAttack: "<< attack <<endl;
    cout<<"\tDefense: "<< defense <<endl;
    cout<<"\tDefense Base: "<< defenseBase <<endl;
    cout<<"\tSpeed: "<< speed <<endl;
    cout<<"\tExperience: "<< experience <<endl;
}

void Player::gainExperience(Enemy* enemy, vector<Enemy *> enemies) {
    int exp = enemy->getExperience();
    experience += exp;

    while(experience>=100){
        int RestoExp = experience - 100;
        experience = RestoExp;
        levelUp();
        for(int i=0; i<enemies.size(); i++){
            if(enemies[1]->getName() != enemy->getName()){
                enemies[i]->levelUp();
            }
        }
    }
    cout << "Current experience: " << experience << endl;
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "\nSelect a target: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    cout<<"\n";
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(vector<Enemy*> enemies) {
    int action = 0;
    cout << "\nSelect an action: " << endl
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

    memcpy(iterator, &maxHealth, sizeof(maxHealth));
    iterator += sizeof(maxHealth);

    memcpy(iterator, &attack, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(iterator, &defense, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(iterator, &defenseBase, sizeof(defenseBase));
    iterator += sizeof(defenseBase);

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
    int health, maxHealth, attack, defense, defenseBase, speed, level, experience;
    bool isPlayer;

    memcpy(&name, iterator, sizeof(name));
    iterator += sizeof(name);

    memcpy(&health, iterator, sizeof(health));
    iterator += sizeof(health);

    memcpy(&maxHealth, iterator, sizeof(maxHealth));
    iterator += sizeof(maxHealth);

    memcpy(&attack, iterator, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(&defense, iterator, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(&defenseBase, iterator, sizeof(defenseBase));
    iterator += sizeof(defenseBase);

    memcpy(&speed, iterator, sizeof(speed));
    iterator += sizeof(speed);

    memcpy(&isPlayer, iterator, sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(&level, iterator, sizeof(level));
    iterator += sizeof(level);

    memcpy(&experience, iterator, sizeof(experience));
    iterator += sizeof(experience);

    return new Player(name, health, maxHealth, attack, defense, speed, isPlayer, level, experience);

}