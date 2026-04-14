#include "BatchCommand.h"

// Constructor definition, calls Command constuructor
BatchCommand::BatchCommand(string option, string argument) : Command(batch, option, argument){}

// execute method definition
void BatchCommand::execute(vector<string>& out, bool& toPrint) {
	// If there is an option, that is an exception
	if (!this->getOption().empty()) {
		throw NoOptionExpected;
	}

	TextHandler& textHandler = TextHandler::getInstance();
	IOHandler& reader= IOHandler::getInstance();

	string argument;
	string inputFile;
	string destinationFile;
	string method;

	string rest = this->getArg();

	// Argument parts get separadted
	textHandler.splitArgumentParts(rest, argument, inputFile, destinationFile, method);

	// In this part commands are read, and also checks for exceptions
	if (!argument.empty()) {
		throw NoArgumentExpected;
	}
	else if (!inputFile.empty()) {
		out = redirectFrom(inputFile);
	}
	else if (argument.empty() && inputFile.empty()) {
		out = reader.readLines();
	}

	// In vector out are commands that need to be executed
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
void BatchCommand::perform(vector<string>& args) {

	Interpreter& interpreter = Interpreter::getInstance();
	TextHandler& textHandler = TextHandler::getInstance();

	vector<string> lines = args;
	args.clear();

	// Every command gets executed
	for (int i = 0; i < lines.size(); i++) {
		vector<string> output;

		vector<string> commands = textHandler.separateCommands(lines[i]);

		// If there are more than one command in one line, that is Pipe
		if (commands.size() == 1) {
			string name;
			string option;
			string argument;
			textHandler.splitCommandParts(lines[i], name, option, argument);

			if ((name == "echo" || name == "tr" || name == "wc" || name == "head") && argument.empty()) {
				continue;
			}
			else if ((name != "date" || name != "time") && !argument.empty()) {
				interpreter.interpret(lines[i], output);
			}
			else {
				interpreter.interpret(lines[i], output);
			}
		}
		else {
			Pipe pipe;
			output = pipe.execute(commands);
		}

		for (int j = 0; j < output.size(); j++) {
			args.push_back(output[j]);
		}
	}
}
