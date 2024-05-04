#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"


int main() {
    Player *player = new Player("Victor", 50, 10, 4, 3);
    Enemy *enemy = new Enemy("Goblin", 30, 6, 2, 5, 10);
    Enemy *enemy2 = new Enemy("Orc", 30, 6, 2, 5, 10);
    Enemy *enemy3 = new Enemy("Little boots", 40, 7, 2, 4, 10);

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);
    participants.push_back(enemy3);

    Combat *combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete combat;
    return 0;
}
