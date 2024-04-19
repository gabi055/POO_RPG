//
// Created by Victor Navarro on 15/02/24.
//

#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H
#include <string>
#include <cstdlib>

using namespace std;

class Character {
protected:
    char name[50];
    int health;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
public:
    Character(const char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer);

    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;
    virtual void defend() = 0;
    virtual void resetDefense() = 0;


    bool flee(Character* target);
    const char* getName();
    int getHealth();
    int getAttack();
    int getDefense();
    bool getIsPlayer();
    int getSpeed();
    const char* toString();
};


#endif //RPG_CHARACTER_H
