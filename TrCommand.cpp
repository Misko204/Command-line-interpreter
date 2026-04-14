#include "TrCommand.h"

// Constructor definition, calls Command constuructor
TrCommand::TrCommand(string option, string argument) : Command(tr, option, argument) {}

// execute method definition
void TrCommand::execute(vector<string>& out, bool& toPrint) {
	// If there is an option, that is an exception
	if (!this->getOption().empty()) {
		throw NoOptionExpected;
	}

	// Three parts of an argument
	string text;
	string what;
	string with;

	TextHandler& textHandler = TextHandler::getInstance();
	IOHandler& reader = IOHandler::getInstance();

	string argument;
	string inputFile;
	string destinationFile;
	string method;
	
	string rest = this->getArg();

	// Argument parts are split
	textHandler.splitArgumentParts(rest, argument, inputFile, destinationFile, method);

	char c = argument[0];

	// Argument parts are divided
	divideArgument(argument, text, what, with);

	// What and with are put together and sent at the back of a vector
	string argRest;

	// What must be given
	if (what.empty()) {
		throw ArgumentMissing;
	}

	// Checks for exceptions and prepares argument for performing
	size_t inputPos = this->getArg().find(inputFile);

	if (!text.empty() && !inputFile.empty() && (inputPos == 0 || this->getArg()[inputPos - 1] != '<')) {
		size_t argPos = this->getArg().find(text);
		if (argPos > inputPos) {
			throw NoArgumentExpected;
		}
		throw InputFileNotExpected;
	}

	if (!inputFile.empty()) {
		out = redirectFrom(inputFile);
	}
	else if (!text.empty()) {
		out.push_back(text);
	}
	else if (text.empty() && inputFile.empty()) {
		out = reader.readLines();
	}

	if (with.empty()) {
		argRest = '"' + what + '"';
	}
	else {
		argRest = '"' + what + '"' + ' ' + '"' + with + '"';
	}

	out.push_back(argRest);

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

// perform method definition, replaces string what in text with string with
void TrCommand::perform(vector<string>& args) {
	TextHandler& textHandler = TextHandler::getInstance();

	string rest = args.back();
	args.pop_back();

	string what = textHandler.extractBetween(rest, '"', '"');
	rest.erase(0, what.size() + 2);

	string with;

	if (rest.size() > 1) {
		rest.erase(0, 1);
		with = textHandler.extractBetween(rest, '"', '"');
	}
	else {
		with = "";
	}

	for (int i = 0; i < args.size(); i++) {
		args[i] = textHandler.replaceSubstring(args[i], what, with);
	}
}

// divideArgument method definition
void TrCommand::divideArgument(string& arg, string& text, string& what, string& with) {
	TextHandler& textHandler = TextHandler::getInstance();

	char c = arg[0];

	text = textHandler.extractBetween(arg, c, '"');

	if (c != '"') {
		text = c + text;
		text.pop_back();
		arg.erase(0, text.size() + 1);
	}
	else {
		arg.erase(0, text.size() + 3);
	}

	what = textHandler.extractBetween(arg, '"', '"');

	arg.erase(0, what.size() + 3);

	with = textHandler.extractBetween(arg, '"', '"');

	arg.erase(0, with.size() + 3);

	if (with.empty() && what.empty()) {
		what = text;
		text.clear();
	}
	else if (with.empty()) {
		with = what;
		what = text;
		text.clear();
	}
}