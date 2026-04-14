#include "TimeCommand.h"

// Constructor definition, calls Command constuructor
TimeCommand::TimeCommand(string option, string argument) : Command(timeCmd, option, argument) {}

// execute method definition
void TimeCommand::execute(vector<string>& out, bool& toPrint) {
	// If there is an option, that is an exception
	if (!this->getOption().empty()) {
		throw NoOptionExpected;
	}

	TextHandler& textHandler = TextHandler::getInstance();

	string method;
	string destinationFile;
	string inputFile;
	string argument;
	string rest = this->getArg();

	// Argument parts get separadted
	textHandler.splitArgumentParts(rest, argument, inputFile, destinationFile, method);

	// Ckeck for exceptions
	if (!argument.empty() || !inputFile.empty()) {
		size_t inputPos = string::npos;
		if (!inputFile.empty()) inputPos = this->getArg().find(inputFile);
		size_t argPos = string::npos;
		if (!argument.empty()) argPos = this->getArg().find(argument);
		if (inputPos < argPos) {
			throw InputFileNotExpected;
		}
		else {
			throw NoArgumentExpected;
		}
	}

	perform(out);

	// If destinationFile isn't empty, output gets redirected there
	if (!destinationFile.empty()) {
		redirectTo(out, destinationFile, method);
		out.clear();
		out.push_back(destinationFile);
		return;
	}

	toPrint = 1;
}

// perform method definition
void TimeCommand::perform(vector<string>& args) {
	time_t t = time(nullptr);
	tm now;
	localtime_s(&now, &t);

	string output = to_string(now.tm_hour) + ':' + to_string(now.tm_min) + ':' + to_string(now.tm_sec);
	args.push_back(output);
}
