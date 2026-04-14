#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <filesystem>

#include "ExceptionHandler.h"

// Class FileHandler, this class handles operations with files
class FileHandler {
public:

	// getInstance method, because FileHandler is singleton
	static FileHandler& getInstance();

	// readFromFile method, reads lines from file and stores them in vector
	vector<string> readFromFile(string fileName);

	// writeInFile method, writes lines from vector in file
	void writeInFile(vector<string> out, string fileName);

private:

	// Constructor is private, because FileHandler is singleton
	FileHandler();

	// Copy constructors are deleted
	FileHandler(const FileHandler&) = delete;

	FileHandler& operator=(const FileHandler&) = delete;
};

#endif