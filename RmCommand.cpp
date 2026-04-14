#include "RmCommand.h"

// Constructor definition, calls Command constuructor
RmCommand::RmCommand(string option, string fileName) : Command(rm, option, fileName) {}

// execute method definition
void RmCommand::execute(vector<string>& out, bool& toPrint) {
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

	out.push_back(inputFile);
	perform(out);
}

// perform method definition
void RmCommand::perform(vector<string>& args) {
	string arg = args[0];
	// Checks if file exists
	if (!filesystem::exists(arg)) {
		throw FileNotFound;
	}
	remove(arg.c_str());
	args.pop_back();
}
