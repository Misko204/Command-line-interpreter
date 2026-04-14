#ifndef ECHOCOMMAND_H
#define ECHOCOMMAND_H

#include "Command.h"

// Echo command, inherits class Command
class EchoCommand : public Command {
public:

	// Constructor
	EchoCommand(string option, string argument);

	// execute method
	void execute(vector<string>& out, bool& toPrint) override;

	// perform method
	void perform(vector<string>& args) override;
};

#endif