#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "Command.h"

// Class Translator, this class translates command name from string to Cmd
class Translator {
public:

	// getInstance method, because Translator is singleton
	static Translator& getInstance();

	// stringToCommand method, this method performs the translation
	Cmd stringToCommand(string commandName);

private:

	// Constructor is private, because Translator is singleton
	Translator();

	// Copy constructors are deleted
	Translator(const Translator&) = delete;

	Translator& operator=(const Translator&) = delete;

};

#endif
