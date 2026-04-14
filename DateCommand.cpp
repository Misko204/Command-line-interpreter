#include "DateCommand.h"

// Constructor definition, calls Command constuructor
DateCommand::DateCommand(string option, string argument) : Command(date, option, argument) {}

// execute method definition
void DateCommand::execute(vector<string>& out, bool& toPrint) {
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
void DateCommand::perform(vector<string>& args) {
	time_t t = time(nullptr);
	tm now;
	localtime_s(&now, &t);

	string output = to_string(now.tm_mday) + '.' + to_string(now.tm_mon + 1) + '.' + to_string(now.tm_year + 1900) + '.';
	args.push_back(output);
}
