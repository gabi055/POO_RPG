#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include "Files/FileHandler.h"

Player* loadPlayerInfo(){
    try{
        char buffer[Player::BUFFER_SIZE];
        FileHandler fileHandler = FileHandler();
        fileHandler.readFromFile("PlayerInfo.data", buffer, Player::BUFFER_SIZE);
        return Player::unserialize(buffer);
    } catch(int error){
        //return new Player("Victor", 5, 10, 4, 3);
        char playerName[100];
       cout << "\nError loading player information. \nEnter the player's name: " << endl;
       cin.getline(playerName, sizeof(playerName));
       return new Player(playerName,60, 60, 10, 4,3);
    }
}

int main() {
    Player *player = loadPlayerInfo();
    Enemy *enemy = new Enemy("Goblin", 30, 30, 6, 2, 4, 100, 1);
    Enemy *enemy2 = new Enemy("Orc", 30, 30,  6, 2, 4, 10,1);
    Enemy *enemy3 = new Enemy("Little boots", 40,40,  7, 2, 4, 10,1);

   // FileHandler *fileHandler = new FileHandler();

   // char* buffer = player->serialize();
    //fileHandler->writeToFile("Personaje1.data", buffer, Player::BUFFER_SIZE);
    //char bufferLectura[Player::BUFFER_SIZE];
   // fileHandler->readFromFile("Personaje1.data", bufferLectura, Player::BUFFER_SIZE);

   // Player *unserializedPlayer = Player::unserialize(bufferLectura);


   // cout << unserializedPlayer->toString();


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
