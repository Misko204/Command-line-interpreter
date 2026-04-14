#include "WcCommand.h"

// Constructor definition, calls Command constuructor
WcCommand::WcCommand(string option, string argument) : Command(wc, option, argument) {}

// execute method definition
void WcCommand::execute(vector<string>& out, bool& toPrint){
	// If otpion is missing, that is an exception
	if (this->getOption().empty()) {
		throw OptionMissing;
	}
	// If option is unknown, that is an exception
	if (this->getOption() != "-w" && this->getOption() != "-c") {
		throw UnknownOption;
	}

	TextHandler& textHandler = TextHandler::getInstance();
	IOHandler& reader = IOHandler::getInstance();

	string inputFile;
	string destinationFile;
	string method;
	string argument;

	string rest = this->getArg();

	// Argument parts are split
	textHandler.splitArgumentParts(rest, argument, inputFile, destinationFile, method);

	size_t inputPos = this->getArg().find(inputFile);

	// In this part input is prepared for perform, and also it checks for exceptions
	if (!argument.empty() && !inputFile.empty() && (inputPos == 0 || this->getArg()[inputPos - 1] != '<')) {
		size_t argPos = this->getArg().find(argument);
		if (argPos > inputPos) {
			throw NoArgumentExpected;
		}
		throw InputFileNotExpected;
	}

	if (!inputFile.empty()) {
		out = redirectFrom(inputFile);
	}
	else if (count(argument.begin(), argument.end(), '"') >= 2) {
		size_t firstQuote = argument.find('"');
		size_t lastQuote = argument.rfind('"');
		argument = textHandler.extractBetweenPositions(argument, firstQuote, lastQuote);
		out.push_back(argument);
	}
	else if (argument.empty() && inputFile.empty()) {
		out = reader.readLines();
	}

	out.push_back(option);
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
void WcCommand::perform(vector<string>& args) {
	string option = args.back();
	args.pop_back();

	int characterCount = 0;
	int wordCount = 0;

	// Words anc characters are counted at the same time
	for (int i = 0; i < args.size(); i++) {
		istringstream iss(args[i]);
		
		string word;
		while (iss >> word) {
			wordCount++;
		}
		characterCount += args[i].size();
	}

	args.clear();

	if (option == "-w") {
		args.push_back(to_string(wordCount));
	} 
	else if (option == "-c") {
		args.push_back(to_string(characterCount));
	}
}
