#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "WcCommand.h"
#include "EchoCommand.h"
#include "TimeCommand.h"
#include "DateCommand.h"
#include "TouchCommand.h"
#include "PromptCommand.h"
#include "TruncateCommand.h"
#include "RmCommand.h"
#include "TrCommand.h"
#include "HeadCommand.h"
#include "BatchCommand.h"

// Class CommandFactory, this class creates commands
class CommandFactory {
public:

	// getInstance method, because CommandFactory is singleton
	static CommandFactory& getInstance();

	// createCommand method
	Command* createCommand(Cmd name, string option, string argument);

private:

	// Constructor is private, because CommandFactory is singleton
	CommandFactory();

	// Copy constructors are deleted
	CommandFactory(const CommandFactory&) = delete;

	CommandFactory& operator=(const CommandFactory&) = delete;
};

#endif

