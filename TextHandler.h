#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include <vector>
#include <sstream>

using namespace std;

// Class TextHandler, this class handles operations with text
class TextHandler {
public:

	// getInstance method, because TextHandler is singleton
	static TextHandler& getInstance();

	// extractBetween method, extracts between two characters
	string extractBetween(string text, char startChar, char endChar);

	// extractBetweenPositions method, extracts between two positions
	string extractBetweenPositions(string text, size_t startPos, size_t endPos);

	// replaceSubstring method, reaplaces substring with another string
	string replaceSubstring(string text, string what, string with);

	// separateCommands method, separates commands divided with |
	vector<string> separateCommands(string line);

	// splitArgumentParts method, splits parts of an argument
	void splitArgumentParts(string& text, string& argument, string& sourceFile, string& destinationFile, string& method);

	// splitCommandParts method, splits command parts, command name, option and argument
	void splitCommandParts(string line, string& name, string& option, string& argument);

private:

	// Constructor is private, because TextHandler is singleton
	TextHandler();

	// Copy constructors are deleted
	TextHandler(const TextHandler&) = delete;

	TextHandler& operator=(const TextHandler&) = delete;

};

#endif