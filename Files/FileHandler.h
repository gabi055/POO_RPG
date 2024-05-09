//
// Created by gabri on 05/05/2024.
//

#ifndef RPG_POO_FILEHANDLER_H
#define RPG_POO_FILEHANDLER_H
#import <fstream>

using namespace std;

class FileHandler {
private:
    ifstream readStream;
    ofstream writeStream;

public:
    void writeToFile(char* targetFilePath, char* buffer, unsigned int bufferSize);
    char* readFromFile(char* targetFilePath, char* buffer, unsigned int bufferSize);
};


#endif //RPG_POO_FILEHANDLER_H
