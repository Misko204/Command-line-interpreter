#ifndef TRCOMMAND_H
#define TRCOMMAND_H

#include "Command.h"

// Tr command, inherits class Command
class TrCommand : public Command {
public:

	// Constructor
	TrCommand(string option, string argument);

	// execute method
	void execute(vector<string>& out, bool& toPrint) override;

	// perform method
	void perform(vector<string>& args) override;

protected:

	// Helper function that divides argument
	void divideArgument(string& arg, string& text, string& what, string& with);
};

#endif