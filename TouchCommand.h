#ifndef TOUCHCOMMAND_H
#define TOUCHCOMMAND_H

#include "Command.h"

// Touch command, inherits class Command
class TouchCommand : public Command {
public:

	// Constructor
	TouchCommand(string option, string fileName);

	// execute method
	void execute(vector<string>& out, bool& toPrint) override;

	// perform method
	void perform(vector<string>& args) override;
};

#endif