#ifndef TIMECOMMAND_H
#define TIMECOMMAND_H

#include "Command.h"

// Time command, inherits class Command
class TimeCommand : public Command {
public:

	// Constructor
	TimeCommand(string option, string argument);

	// execute method
	void execute(vector<string>& out, bool& toPrint) override;

	// perform method
	void perform(vector<string>& args) override;

};

#endif