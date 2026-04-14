#include "FileHandler.h"

// Returns instance of single object
FileHandler& FileHandler::getInstance() {
    static FileHandler instance;
    return instance;
}

// readFromFile method definition
vector<string> FileHandler::readFromFile(string fileName) {
    vector<string> fileLines;

    ifstream file(fileName);

    if (!filesystem::exists(fileName)) {
        throw FileNotFound;
    }

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            fileLines.push_back(line);
        }
        file.close();
    }
    else {
        throw FileAccessException;
    }

    return fileLines;
}

// writeInFile method definition
void FileHandler::writeInFile(vector<string> out, string fileName) {
    ofstream file(fileName, ios::app);
    if (!file) {
        throw FileAccessException;
    }

    for (int i = 0; i < out.size(); i++) {
        file << out[i];
    }

    file.close();
}

FileHandler::FileHandler() {}