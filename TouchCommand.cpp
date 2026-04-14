#include "TouchCommand.h"

// Constructor definition, calls Command constuructor
TouchCommand::TouchCommand(string option, string fileName) : Command(touch, option, fileName) {}

// execute method definition
void TouchCommand::execute(vector<string>& out, bool& toPrint){
	// If there is an option, that is an exception
	if (!this->getOption().empty()) {
		throw NoOptionExpected;
	}

	TextHandler& textHandler = TextHandler::getInstance();

	string inputFile;
	string destinationFile;
	string argument;
	string method;
	string rest = this->getArg();

	// If argument, input redirect or destination file were found, that is an exception
	textHandler.splitArgumentParts(rest, argument, inputFile, destinationFile, method);

	size_t inputPos = this->getArg().find('<');

	if (!argument.empty() || !inputFile.empty() || !destinationFile.empty()) {
		size_t argPos = string::npos;
		if (!argument.empty()) {
			argPos = this->getArg().find(argument);
		}
		size_t outputPos = this->getArg().find('>');

		if (inputPos != string::npos && (argPos == string::npos || inputPos < argPos) && (outputPos == string::npos || inputPos < outputPos)) {
			throw InputFileNotExpected;
		}

		if (argPos != string::npos && (inputPos == string::npos || argPos < inputPos) && (outputPos == string::npos || argPos < outputPos)) {
			throw NoArgumentExpected;
		}

		if (outputPos != string::npos && (inputPos == string::npos || outputPos < inputPos) && (argPos == string::npos || outputPos < argPos)) {
			throw OutputFileNotExpected;
		}
	}

	// Checks if file exists
	if (filesystem::exists(this->getArg())) {
		throw FileNotFound;
	}

	// If not exists, perform method is called to create it
	out.push_back(this->getArg());
	perform(out);
}

// perform method definition
void TouchCommand::perform(vector<string>& args) {
	ofstream file(args[0]);
	args.pop_back();

	// If file doesn't exists after creation, it is an exception
	if (!file) {
		throw FileAccessException;
	}

	// File is open when it is made, so it needs to be closed
	file.close();

	
}
