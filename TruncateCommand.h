#ifndef TRUNCATECOMMAND_H
#define TRUNCATECOMMAND_H

#include "Command.h"

// Truncate command, inherits class Command
class TruncateCommand : public Command {
public:
	
	//Constructor
	TruncateCommand(string option, string fileName);

	// execute method
	void execute(vector<string>& out, bool& toPrint) override;

	// perform method
	void perform(vector<string>& args) override;
};

#endif