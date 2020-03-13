#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ZorkUL
{
    private:
        Parser parser;
        Room* currentRoom;
        Room* spawnRoom;
        Room* exitRoom;
        vector<Room> roomList;
        void createWorld();
        void printWelcome();
        bool processCommand(Command command);
        void printHelp();
        void createItems();
        void displayItems();
    public:
        string teleport();
        Room* randomRoomSelection();
        string goRoom(Command command);
        ZorkUL();
        void play();
        string go(string direction);
};
#endif /*ZORKUL_H_*/
