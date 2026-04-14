#include "TruncateCommand.h"

// Constructor definition, calls Command constuructor
TruncateCommand::TruncateCommand(string option, string fileName) : Command(truncate, option, fileName){}

// execute method definition
void TruncateCommand::execute(vector<string>& out, bool& toPrint) {
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

	// First checks if file exists
	if (!filesystem::exists(this->getArg())) {
		throw FileNotFound;
	}
	string arg = this->getArg();
	out.push_back(arg);

	perform(out);
}

// perform method definition
void TruncateCommand::perform(vector<string>& args) {
	ofstream file(args[0], ios::trunc);
	args.pop_back();

	if (!file) {
		throw FileAccessException;
	}
	file.close();
}
