#ifndef RMCOMMAND_H
#define RMCOMMAND_H

#include "Command.h"

// Rm command, inherits class Command
class RmCommand : public Command {
public:

	// Constructor
	RmCommand(string option, string fileName);

	// execute method
	void execute(vector<string>& out, bool& toPrint) override;

	// perform method
	void perform(vector<string>& args) override;
};

#endif