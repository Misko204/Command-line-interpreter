#ifndef PROMPTCOMMAND_H
#define PROMPTCOMMAND_H

#include "Command.h"

// Prompt command, inherits class Command
class PromptCommand : public Command {
public:

	// Constructor
	PromptCommand(string option, string argument);

	// execute method
	void execute(vector<string>& out, bool& toPrint) override;

	// perform method
	void perform(vector<string>& args) override;
};

#endif

