//
// Created by Victor Navarro on 15/02/24.
//
#pragma once
#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H
#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"
#include <vector>
class Enemy;

class Player: public Character {
    //TODO: Implement Classes (Mage, Warrior, Rogue, etc..)
    //TODO: Implement Inventory
private:
    int level;
    int experience;
    void SaveProgress();
public:
    Player(const char* _name, int _health, int _maxHealth,  int _attack, int _defense, int _speed);
    Player(const char* _name, int _health, int _maxHealth, int _attack, int _defense, int _speed, bool _isPlayer, int _level, int _experience);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    void levelUp();
    Character* selectTarget(vector<Enemy*> possibleTargets);
    Action takeAction(vector<Enemy*> enemies);
    char* serialize();
    static Player* unserialize(char* buffer);

    void gainExperience(Enemy* enemy, vector<Enemy *> enemies);
    static const unsigned int BUFFER_SIZE = sizeof (name) + sizeof (health) + sizeof(maxHealth) + sizeof(attack) + sizeof(defense) + sizeof(defenseBase) + sizeof(speed) + sizeof(isPlayer) + sizeof(level) + sizeof(experience);

    //TODO: Implement use object
    //void resetDefense();
private:
    char buffer[Player::BUFFER_SIZE];
};


#endif //RPG_PLAYER_H
