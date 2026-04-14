#ifndef BATCHCOMMAND_H
#define BATCHCOMMAND_H

#include "Command.h"
#include "Pipe.h"

// Batch command, inherits class Command
class BatchCommand : public Command {
public:

	// Constructor
	BatchCommand(string option, string argument);

	// execute method
	void execute(vector<string>& out, bool& toPrint) override;

	// perform method
	void perform(vector<string>& args) override;
};

#endif