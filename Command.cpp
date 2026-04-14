#include "Command.h"

// Constructor definition
Command::Command(Cmd name, string option, string argument) : commandName(name), option(option), argument(argument){}

// redirectFrom method definition, it reads from file and retunrs what it read
vector<string> Command::redirectFrom(string fileName) {
	vector<string> input;
	FileHandler& fileHandler = FileHandler::getInstance();

	input = fileHandler.readFromFile(fileName);

	return input;
}

// redirectTo method definition, it writes in designated file
void Command::redirectTo(vector<string> output, string fileName, string method) {
	FileHandler& fileHandler = FileHandler::getInstance();
	
	// If method is ">" than it should delete from file first, and after that it shoud write
	if (method == ">") {
		ofstream file(fileName, ios::trunc);
		if (file.is_open()) {
			file.close();
		}
		for (int i = 0; i < output.size(); i++) {
			if (i != output.size() - 1) {
				output[i] += '\n';
			}
		}
	}

	fileHandler.writeInFile(output, fileName);
}

// getName method definition
Cmd Command::getName() const {
	return commandName;
}

// getOption method definition
string Command::getOption() const {
    return option;
}

// getArg method definition
string Command::getArg() const {
	return argument;
}

// Destructor
Command::~Command() {}