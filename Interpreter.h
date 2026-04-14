#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

// Class Interpreter, this class interprets commands
class Interpreter {
public:

	// getInstance method, because Interpreter is singleton
	static Interpreter& getInstance();

	// interpret method, interprets command given in input
	void interpret(string input, vector<string>& output);

	// Returns ready sign
	string getReadySign();

	// Sets ready sign to new sign
	void setReadySign(string newSign);

private:

	// Constructor is private, because Interpreter is singleton
	Interpreter();

	// Copy constructors are deleted
	Interpreter(const Interpreter&) = delete;

	Interpreter& operator=(const Interpreter&) = delete;

	// Starting ready sign is $
	string readySign = "$";
};

#endif