#include "EchoCommand.h"

// // Constructor definition, calls Command constuructor
EchoCommand::EchoCommand(string option, string argument) : Command(echo, option, argument) {}

// execute method definition
void EchoCommand::execute(vector<string>& out, bool& toPrint) {
	// If there is an option, that is an exception
	if (!this->getOption().empty()) {
		throw NoOptionExpected;
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

	size_t inputPos = this->getArg().find(inputFile);

	// In this part, argument is extracted or lines are read, and also checks for exceptions
	if (!argument.empty() && !inputFile.empty() && (inputPos == 0 || this->getArg()[inputPos - 1] != '<')) {
		size_t argPos = this->getArg().find(argument);
		if (argPos > inputPos) {
			throw NoArgumentExpected;
		}
		throw InputFileNotExpected;
	}
	else if (!inputFile.empty() && ((inputPos > 0 && this->getArg()[inputPos - 1] == '<') || argument.empty())) {
		out = redirectFrom(inputFile);
	}
	else if (!argument.empty() && count(argument.begin(), argument.end(), '"') >= 2) {
		size_t firstQuote = argument.find('"');
		size_t lastQuote = argument.rfind('"');
		argument = textHandler.extractBetweenPositions(argument, firstQuote, lastQuote);
		out.push_back(argument);
	}
	else if (argument.empty() && inputFile.empty()) {
		out = reader.readLines();
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

// perform method definition, does nothing
void EchoCommand::perform(vector<string>& args) {
	return;
}
