#ifndef COMMANDWORDS_H_
#define COMMANDWORDS_H_

#include <iostream.h>
#include <string.h>
#include <vector.h>
using namespace std;

class CommandWords {
private:
	//Define a static vector for our valid command words.
	//We'll populate this in the class constructor
	static vector<string.h> validCommands;

public:
	CommandWords();
	bool isCommand(string aString);
	void showAll();
};


#endif /*COMMANDWORDS_H_*/
