#include "PromptCommand.h"

// Constructor definition, calls Command constuructor
PromptCommand::PromptCommand(string option, string argument) : Command(prompt, option, argument){}

// execute method definition
void PromptCommand::execute(vector<string>& out, bool& toPrint) {
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

	// If input file or destination file were found, that is an exception
	textHandler.splitArgumentParts(rest, argument, inputFile, destinationFile, method);

	// Extracts argument from quotes and checks for exceptions
	size_t firstQuote = argument.find('"');
	size_t lastQuote = argument.rfind('"');
	if (firstQuote == string::npos || lastQuote == string::npos) {
		throw ArgumentMissing;
	}
	if (!inputFile.empty() || !destinationFile.empty()) {
		size_t inputPos = this->getArg().find(inputFile);
		size_t outputPos = this->getArg().find(destinationFile);
		if (inputPos == string::npos) {
			outputPos = 0;
		}
		if (outputPos == string::npos) {
			inputPos = 0;
		}
		if (inputPos > outputPos) {
			throw OutputFileNotExpected;
		}
		throw InputFileNotExpected;
	}
	argument = textHandler.extractBetweenPositions(argument, firstQuote, lastQuote);
	out.push_back(argument);
	perform(out);
}

// perform method definition
void PromptCommand::perform(vector<string>& args) {
	Interpreter& interpreter = Interpreter::getInstance();
	string argument = args[0];
	interpreter.setReadySign(argument);
	args.pop_back();
}
