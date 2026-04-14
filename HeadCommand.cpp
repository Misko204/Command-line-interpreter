#include "HeadCommand.h"

// Constructor definition, calls Command constuructor
HeadCommand::HeadCommand(string option, string argument) : Command(head, option, argument) {}

// execute method definition
void HeadCommand::execute(vector<string>& out, bool& toPrint) {
	// If there is not an option, that is an exception
	if (this->getOption().empty()) {
		throw OptionMissing;
	}

	// If option is unknown or number is too big, that is an exception
	int count = stoi(this->getOption().erase(0, 2));
	if (this->getOption().substr(0, 2) != "-n" || count > 99999) {
		throw UnknownOption;
	}

	TextHandler& textHandler = TextHandler::getInstance();
	IOHandler& reader = IOHandler::getInstance();

	string argument;
	string inputFile;
	string destinationFile;
	string method;
	string rest = this->getArg();

	// Argument parts get separadted
	textHandler.splitArgumentParts(rest, argument, inputFile, destinationFile, method);

	// In this part lines are read and also checks for exceptions
	if (!argument.empty()) {
		throw NoArgumentExpected;
	}
	else if (!inputFile.empty()) {
		out = redirectFrom(inputFile);
	}
	else if (argument.empty() && inputFile.empty()) {
		out = reader.readLines();
	}

	// option gets placed at the end of vector
	out.push_back(this->getOption());
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
void HeadCommand::perform(vector<string>& args) {
	string option = args.back();
	args.pop_back();

	int count = stoi(option.erase(0, 2));

	size_t length = option.size();

	while (args.size() > count) {
		args.pop_back();
	}
}
