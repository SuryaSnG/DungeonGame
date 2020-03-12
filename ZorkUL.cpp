#include <iostream.h>
#include <time.h>
#include <stdlib.h>
#include <algorithm.h>

using namespace std;
#include "ZorkUL.h"

int main() {
    ZorkUL temp;
    temp.play();
    return 0;
}

ZorkUL::ZorkUL() {
	createRooms();
}

void ZorkUL::createRooms()  {
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;

	a = new Room("a");
        a->addItem(new Item("x", 1, 11));
        a->addItem(new Item("y", 2, 22));
	b = new Room("b");
        b->addItem(new Item("xx", 3, 33));
        b->addItem(new Item("yy", 4, 44));
	c = new Room("c");
	d = new Room("d");
	e = new Room("e");
	f = new Room("f");
	g = new Room("g");
	h = new Room("h");
	i = new Room("i");
    j = new Room("j");

    //(N, E, S, W)
    a->setExits(f, b, d, c);
    b->setExits(NULL, j, NULL, a);
    c->setExits(NULL, a, NULL, NULL);
    d->setExits(a, e, NULL, i);
    e->setExits(NULL, NULL, NULL, d);
    f->setExits(NULL, g, a, h);
    g->setExits(NULL, NULL, NULL, f);
    h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL);
    j->setExits(NULL, NULL, NULL, b);

    roomList.empty();
    roomList.push_back(*a);
    roomList.push_back(*b);
    roomList.push_back(*c);
    roomList.push_back(*d);
    roomList.push_back(*e);
    roomList.push_back(*f);
    roomList.push_back(*g);
    roomList.push_back(*h);
    roomList.push_back(*i);
    roomList.push_back(*j);

    currentRoom = a;
}

/**
 *  Main play routine.  Loops until end of play.
 */
void ZorkUL::play() {
	printWelcome();

	// Enter the main command loop.  Here we repeatedly read commands and
	// execute them until the ZorkUL game is over.

	bool finished = false;
	while (!finished) {
		// Create pointer to command and give it a command.
		Command* command = parser.getCommand();
		// Pass dereferenced command and check for end of game.
		finished = processCommand(*command);
		// Free the memory allocated by "parser.getCommand()"
		//   with ("return new Command(...)")
		delete command;
	}
	cout << endl;
	cout << "end" << endl;
}

void ZorkUL::printWelcome() {
	cout << "start"<< endl;
	cout << "info for help"<< endl;
	cout << endl;
	cout << currentRoom->longDescription() << endl;
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
bool ZorkUL::processCommand(Command command) {
	if (command.isUnknown()) {
		cout << "invalid input"<< endl;
		return false;
	}

	string commandWord = command.getCommandWord();
	if (commandWord.compare("info") == 0)
		printHelp();

	else if (commandWord.compare("map") == 0)
		{
        cout << "[h] --- [f] --- [g]" << endl;
		cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[c] --- [a] --- [b] --- [j]" << endl;
		cout << "         |         " << endl;
		cout << "         |         " << endl;
		cout << "[i] --- [d] --- [e]" << endl;
		}
    else if(commandWord.compare("teleport") == 0)
    {
        teleport();
    }

	else if (commandWord.compare("go") == 0)
		goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
       	if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
         if (command.hasSecondWord()) {
        cout << "you're trying to take " + command.getSecondWord() << endl;
        int location = currentRoom->isItemInRoom(command.getSecondWord());
        if (location  < 0 )
            cout << "item is not in room" << endl;
        else
            cout << "item is in room" << endl;
            cout << "index number " << + location << endl;
            cout << endl;
            cout << currentRoom->longDescription() << endl;
        }
    }

    else if (commandWord.compare("put") == 0)
    {

    }
    /*
    {
    if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
            if (command.hasSecondWord()) {
            cout << "you're adding " + command.getSecondWord() << endl;
            itemsInRoom.push_Back;
        }
    }
*/
    else if (commandWord.compare("quit") == 0) {
		if (command.hasSecondWord())
			cout << "overdefined input"<< endl;
		else
			return true; /**signal to quit*/
	}
	return false;
}
/** COMMANDS **/
void ZorkUL::printHelp() {
	cout << "valid inputs are; " << endl;
	parser.showCommands();

}

string ZorkUL::teleport()
{
    int r = 0;
    bool temp = true;
    Room *teleportRoom;
    while(temp)
    {
        srand (time(NULL));
        r = rand() % 10;
        switch(r)
        {
            case 0:
            teleportRoom = &roomList.at(0);
            break;
            case 1:
            teleportRoom = &roomList.at(1);
            break;
            case 2:
            teleportRoom = &roomList.at(2);
            break;
            case 3:
            teleportRoom = &roomList.at(3);
            break;
            case 4:
            teleportRoom = &roomList.at(4);
            break;
            case 5:
            teleportRoom = &roomList.at(5);
            break;
            case 6:
            teleportRoom = &roomList.at(6);
            break;
            case 7:
            teleportRoom = &roomList.at(7);
            break;
            case 8:
            teleportRoom = &roomList.at(8);
            break;
            case 9:
            teleportRoom = &roomList.at(9);
            break;
         }
        if(teleportRoom != currentRoom)
        {
            temp = false;
            currentRoom=teleportRoom;
        }
    }
    return("teleporting...\n" + currentRoom->longDescription() + "\n");
}
string ZorkUL::goRoom(Command command) {
	if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        return "incomplete input";
	}

	string direction = command.getSecondWord();

	// Try to leave current room.
	Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL){
		cout << "underdefined input"<< endl;
        return("underdefined input");
    }
	else {
		currentRoom = nextRoom;
		cout << currentRoom->longDescription() << endl;
	}
    return(currentRoom->longDescription() + "\n");
}

string ZorkUL::go(string direction) {
	//Make the direction lowercase
	//transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
	//Move to the next room
	Room* nextRoom = currentRoom->nextRoom(direction);
	if (nextRoom == NULL)
		return("direction null");
	else
	{
		currentRoom = nextRoom;
		return currentRoom->longDescription();
	}
}
