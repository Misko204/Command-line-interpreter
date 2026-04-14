#ifndef WCCOMMAND_H
#define WCCOMMAND_H

#include "Command.h"

// Wc command, inherits class Command
class WcCommand : public Command {
public:

	// Constructor
	WcCommand(string option, string argument);

	// execute method
	void execute(vector<string>& out, bool& toPrint) override;

	// perform method
	void perform(vector<string>& args) override;
};

#endif