#ifndef HEADCOMMAND_H
#define HEADCOMMAND_H

#include "Command.h"

// Head command, inherits class Command
class HeadCommand : public Command {
public:

	// Constructor
	HeadCommand(string option, string argument);

	// execute method
	void execute(vector<string>& out, bool& toPrint) override;

	// perform method
	void perform(vector<string>& args) override;
};

#endif