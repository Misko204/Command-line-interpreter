#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include "TextHandler.h"
#include "Interpreter.h"

// All possible exceptions
enum Exception { 
	NoOptionExpected, OptionMissing, UnknownOption, 
	NoArgumentExpected, ArgumentMissing, 
	InputFileNotExpected, OutputFileNotExpected, FileNotFound, FileAccessException, 
	UnknownCommand 
};

// Class ExceptionHandler, this class handles exceptions
class ExceptionHandler {
public:

	// getInstance method, because ExceptionHandler is singleton
	static ExceptionHandler& getInstance();

	// handle method, depending on exceptions, handles it properly
	void handle(Exception exception, string input, vector<string>& output);

	// Ckecks for invalid characters
	bool checkForInvalidCharacters(string line, vector<string>& out);

protected:

	// Handles UnknownCommand exception
	void unknownCommand(string line, vector<string>& out);

	// Handles NoOptionExpected exception
	void noOptExpected(string line, vector<string>& out);

	// Handles OptionMissing exception
	void optionMissing(string line, vector<string>& out);

	// Handles UnknownOption exception
	void unknownOption(string line, vector<string>& out);

	// Handles NoArgumentExpected exception
	void noArgExpected(string line, vector<string>& out);

	// Handles ArgumentMissing exception
	void argumentMissing(string line, vector<string>& out);

	// Handles InputFileNotExpected exception
	void inputFileNotExpected(string line, vector<string>& out);

	// Handles OutputFileNotExpected exception
	void outputFileNotExpected(string line, vector<string>& out);

	// Handles FileNotFound exception
	void fileNotFound(string line, vector<string>& out);

	// Handles FileAccessException exception
	void fileAccessException(string line, vector<string>& out);

	// Points to certain position
	void point(string line, vector<string>& out, size_t pos);

	// Checks if character belongs to target string
	bool belongsTo(string source, string target, char ch, size_t pos);

private:

	// Constructor is private, because ExceptionHandler is singleton
	ExceptionHandler();

	// Copy constructors are deleted
	ExceptionHandler(const ExceptionHandler&) = delete;

	ExceptionHandler& operator=(const ExceptionHandler&) = delete;
};

#endif