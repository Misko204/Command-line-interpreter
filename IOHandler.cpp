#include "IOHandler.h"

// getInstance method definition
IOHandler& IOHandler::getInstance() {
	static IOHandler instance;
	return instance;
}

// readLine method definition
string IOHandler::readLine() {
	string input;
	getline(cin, input);

	if (input.empty()) return "";

	char last = input.back();

	// If line is longer than 512 characters, it gets resized to 512 characters
	if (input.size() > 512) {
		input.resize(512);

		// If last character before resize was double quotes, they stay last character of new string
		if (last == '"') {
			input.back() = last;
		}
	}
	return input;
}

// readLines method definition
vector<string> IOHandler::readLines() {
	vector<string> lines;
	string oneLine;

	while (getline(cin, oneLine)) {
		lines.push_back(oneLine);
	}
	cin.clear();

	return lines;
}

// print method definition, prints every character one by one
void IOHandler::printOutput(vector<string> output) {
	for (int i = 0; i < output.size(); i++) {
		for (int j = 0; j < output[i].size(); j++) {

			// If character is '\' it gets checked for potentional new line symbol or tab symbol
			if (output[i][j] == '\\') {
				if (j < output[i].size() - 1 && output[i][j + 1] == 'n') {
					cout << endl;
					++j;
				}
				else if (j < output[i].size() - 1 && output[i][j + 1] == 't') {
					cout << '\t';
					++j;
				}
				else {
					cout << output[i][j];
				}
			}
			else {
				cout << output[i][j];
			}
		}
		cout << endl;
	}
}

IOHandler::IOHandler() {}