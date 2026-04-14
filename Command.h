#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "Interpreter.h"
#include "TextHandler.h"
#include "FileHandler.h"
#include "IOHandler.h"
#include "ExceptionHandler.h"

using namespace std;
using namespace chrono;

enum Cmd {echo, date, timeCmd, touch, wc, prompt, truncate, rm, tr, head, batch};

// Abstract class Command, every specific command inherits this class
class Command {
public:
	
	// Method execute, it is called to process arguments and call method perform
	virtual void execute(vector<string>& out, bool& toPrint) = 0;

	// Method perform, just performs what is command supposed to do
	virtual void perform(vector<string>& args) = 0;

	// Redirects input to be read from designated file
	virtual vector<string> redirectFrom(string fileName);

	// Redirects output to designated file
	virtual void redirectTo(vector<string> output, string fileName, string method);

	// Returns command name, same for every command
	virtual Cmd getName() const;

	// Returns command option, same for every command
	virtual string getOption() const;

	// Returns command argument, same for every command
	virtual string getArg() const;

	// Destructor, if needed subclass can redefine it
	virtual ~Command();

protected:

	// Constructor, it is protected so that not everyone can create an instance
	Command(Cmd name, string option, string argument);

	// Command name
	Cmd commandName;

	// Command option
	string option;

	// Command argument
	string argument;
};

#endif
