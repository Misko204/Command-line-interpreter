#ifndef PIPE_H
#define PIPE_H

#include "CommandFactory.h"
#include "Translator.h"
#include "TextHandler.h"
#include "ExceptionHandler.h"

// Class Pipe, it handles pipe input
class Pipe {
public:

	// execute method
	vector<string> execute(vector<string> commands);
};

#endif