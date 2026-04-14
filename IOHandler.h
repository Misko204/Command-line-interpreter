#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

// Class IOHadnler, it handles input and output
class IOHandler {
public:

	// getInstance method, because IOHandler is singleton
	static IOHandler& getInstance();
	
	// readLine method, reads one line from console
	string readLine();

	// readLines method, reads multiple lines from console
	vector<string> readLines();

	// printOutput method, sends every line from vector to stadard output
	void printOutput(vector<string> output);

private:

	// Constructor is private, because IOHandler is singleton
	IOHandler();

	// Copy constructors are deleted
	IOHandler(const IOHandler&) = delete;

	IOHandler& operator=(const IOHandler&) = delete;
};

#endif