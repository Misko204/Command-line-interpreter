#include "Translator.h"

// Returns instance of single object
Translator& Translator::getInstance() {
	static Translator instance;
	return instance;
}

// stringToCommand method definition
Cmd Translator::stringToCommand(string commandName) {
	if (commandName == "echo") return echo;
	else if (commandName == "date") return date;
	else if (commandName == "time") return timeCmd;
	else if (commandName == "touch") return touch;
	else if (commandName == "wc") return wc;
	else if (commandName == "prompt") return prompt;
	else if (commandName == "truncate") return truncate;
	else if (commandName == "rm") return rm;
	else if (commandName == "tr") return tr;
	else if (commandName == "head") return head;
	else if (commandName == "batch") return batch;
	else throw UnknownCommand;
}

Translator::Translator() {}
