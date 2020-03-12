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

class ZorkUL {
private:
	Parser parser;
	Room *currentRoom;
    vector<Room> roomList;
	void createRooms();
	void printWelcome();
	bool processCommand(Command command);
    void printHelp();
    void createItems();
    void displayItems();

public:
    string teleport();
    string goRoom(Command command);
	ZorkUL();
	void play();
	string go(string direction);
};

#endif /*ZORKUL_H_*/
