#include "ExceptionHandler.h"

// getInstance method definition
ExceptionHandler& ExceptionHandler::getInstance() {
	static ExceptionHandler instance;
	return instance;
}

// handle method definition, depending on exception, it calls right method
void ExceptionHandler::handle(Exception exception, string input, vector<string>& output) {
	switch (exception) {
		case UnknownCommand: unknownCommand(input, output); break;
		case NoOptionExpected: noOptExpected(input, output); break;
		case OptionMissing: optionMissing(input, output); break;
		case UnknownOption: unknownOption(input, output); break;
		case NoArgumentExpected: noArgExpected(input, output); break;
		case ArgumentMissing: argumentMissing(input, output); break;
		case InputFileNotExpected: inputFileNotExpected(input, output); break;
		case OutputFileNotExpected: outputFileNotExpected(input, output); break;
		case FileNotFound: fileNotFound(input, output); break;
		case FileAccessException: fileAccessException(input, output); break;
	}
}

// checkForInvalidCharacters method definition, returns false if there is invalid character
bool ExceptionHandler::checkForInvalidCharacters(string line, vector<string>& out) {
	string commandName;
	string option;
	string rest;

	string inputFile;
	string outputFile;
	string argument;
	string method;

	TextHandler& textHandler = TextHandler::getInstance();

	textHandler.splitCommandParts(line, commandName, option, rest);

	textHandler.splitArgumentParts(rest, argument, inputFile, outputFile, method);

	// Checks every character of input line if it is invalid
	for (size_t i = 0; i < line.size(); i++) {
		char c = line[i];
		if (!isalnum(c) && c != '>' && c != '<' && c != '|' && c != ' ' && c != '\t') {
			bool status;
			if (isalnum(c)) {
				status = belongsTo(line, commandName, c, i);
				if (status) continue;
			}

			status = belongsTo(line, option, c, i); if (status) continue;

			status = belongsTo(line, argument, c, i); if (status) continue;

			status = belongsTo(line, inputFile, c, i); if (status && (c == '.' || c == '\\' || c == ':' || c == '_' || c == '/')) continue;

			status = belongsTo(line, outputFile, c, i); if (status && (c == '.' || c == '\\' || c == ':' || c == '_' || c == '/')) continue;

			status = belongsTo(line, rest, c, i); if (status && (c == '.' || c == '\\' || c == ':' || c == '_' || c == '/')) continue;

			out.push_back("Greska! Neocekivani karakter!");

			point(line, out, i);
			return false;
		}
	}
	return true;
}

// unknownCommand method definition
void ExceptionHandler::unknownCommand(string line, vector<string>& out) {
	string commandName;
	string option;
	string argument;
	TextHandler& textHandler = TextHandler::getInstance();

	textHandler.splitCommandParts(line, commandName, option, argument);
	out.push_back("Greska! Komanda " + commandName + " " + "ne postoji!");
}

// noOptExpected method definition
void ExceptionHandler::noOptExpected(string line, vector<string>& out) {
	string commandName;
	string option;
	string argument;
	TextHandler& textHandler = TextHandler::getInstance();
	Interpreter& interpreter = Interpreter::getInstance();
	string readySign = interpreter.getReadySign();

	textHandler.splitCommandParts(line, commandName, option, argument);
	size_t optPos = line.find(option);
	out.push_back("Greska! Komanda " + commandName + " nema opcije!");
	point(line, out, optPos);
}

// optionMissing method definition
void ExceptionHandler::optionMissing(string line, vector<string>& out) {
	string commandName;
	string option;
	string argument;
	TextHandler& textHandler = TextHandler::getInstance();
	Interpreter& interpreter = Interpreter::getInstance();
	string readySign = interpreter.getReadySign();

	textHandler.splitCommandParts(line, commandName, option, argument);
	out.push_back("Greska! Komanda " + commandName + " ocekuje opciju!");
	size_t pos = commandName.size();
	point(line, out, pos);
}

// unknownOption method definition
void ExceptionHandler::unknownOption(string line, vector<string>& out) {
	string commandName;
	string option;
	string argument;
	TextHandler& textHandler = TextHandler::getInstance();
	Interpreter& interpreter = Interpreter::getInstance();
	string readySign = interpreter.getReadySign();

	textHandler.splitCommandParts(line, commandName, option, argument);
	if (commandName == "head" && option.substr(0, 2) == "-n") {
		out.push_back("Greska! Predugacak broj!");
		size_t optPos = line.find(option) + 2;
		point(line, out, optPos);
		return;
	}
	out.push_back("Greska! Opcija " + option + " ne postoji u okviru komande " + commandName + '!');
	size_t optPos = line.find(option) + 1;
	point(line, out, optPos);

}

// noArgExpected method definition
void ExceptionHandler::noArgExpected(string line, vector<string>& out) {
	string commandName;
	string option;
	string argument;
	TextHandler& textHandler = TextHandler::getInstance();
	Interpreter& interpreter = Interpreter::getInstance();
	string readySign = interpreter.getReadySign();

	textHandler.splitCommandParts(line, commandName, option, argument);

	string inputFile;
	string destinationFile;
	string arg;
	string method;

	textHandler.splitArgumentParts(argument, arg, inputFile, destinationFile, method);

	if (commandName == "time" || commandName == "date") {
		out.push_back("Greska! Komanda " + commandName + " nema argument!");
	}
	else {
		out.push_back("Greska! Na ovom mestu nije ocekivan argument pod navodnicima!");
	}

	size_t pos = line.find(arg);
	point(line, out, pos);
}

// argumentMissing method definition
void ExceptionHandler::argumentMissing(string line, vector<string>& out) {
	string commandName;
	string option;
	string argument;
	TextHandler& textHandler = TextHandler::getInstance();
	Interpreter& interpreter = Interpreter::getInstance();
	string readySign = interpreter.getReadySign();

	textHandler.splitCommandParts(line, commandName, option, argument);

	string inputFile;
	string destinationFile;
	string arg;
	string method;

	textHandler.splitArgumentParts(argument, arg, inputFile, destinationFile, method);

	if (commandName == "tr") {
		out.push_back("Greska! Komanda " + commandName + " ocekuje what izmedju navodnika!");
		size_t pos;
		if (line[line.find(inputFile)] != '<') {
			pos = commandName.size() + inputFile.size() + 1;
		}
		else {
			pos = commandName.size();
		}
		point(line, out, pos);
		return;
		
	}
	out.push_back("Greska! Komanda " + commandName + " ocekuje argument!");
	size_t pos = commandName.size() + option.size();
	point(line, out, pos);
}

// inputFileNotExpected definition
void ExceptionHandler::inputFileNotExpected(string line, vector<string>& out) {
	string commandName;
	string option;
	string argument;
	TextHandler& textHandler = TextHandler::getInstance();
	Interpreter& interpreter = Interpreter::getInstance();
	string readySign = interpreter.getReadySign();

	textHandler.splitCommandParts(line, commandName, option, argument);

	string inputFile;
	string destinationFile;
	string arg;
	string method;

	textHandler.splitArgumentParts(argument, arg, inputFile, destinationFile, method);
	
	out.push_back("Greska! Na ovom mestu nije ocekivan ulazni fajl!");
	size_t pos = line.find(inputFile);
	if (pos > 0 && line[pos - 1] == '<') {
		pos = pos - 1;
	}

	point(line, out, pos);

}

// outputFileNotExpected method definition
void ExceptionHandler::outputFileNotExpected(string line, vector<string>& out) {
	string commandName;
	string option;
	string argument;
	TextHandler& textHandler = TextHandler::getInstance();
	Interpreter& interpreter = Interpreter::getInstance();
	string readySign = interpreter.getReadySign();

	textHandler.splitCommandParts(line, commandName, option, argument);

	string inputFile;
	string destinationFile;
	string arg;
	string method;

	textHandler.splitArgumentParts(argument, arg, inputFile, destinationFile, method);

	out.push_back("Greska! Na ovom mestu nije ocekivan izlazni fajl!");
	size_t pos = line.find(destinationFile);
	if (pos > 0 && line[pos - 1] == '>') {
		pos = pos - 1;
	}
	if (pos > 0 && line[pos - 1] == '>') {
		pos = pos - 1;
	}

	point(line, out, pos);
}

// fileNotFound method definition
void ExceptionHandler::fileNotFound(string line, vector<string>& out) {
	string commandName;
	string option;
	string argument;
	TextHandler& textHandler = TextHandler::getInstance();

	textHandler.splitCommandParts(line, commandName, option, argument);

	string inputFile;
	string destinationFile;
	string arg;
	string method;

	textHandler.splitArgumentParts(argument, arg, inputFile, destinationFile, method);

	if (commandName == "touch") {
		out.push_back("Greska! Fajl sa imenom " + inputFile + " vec postoji!");
		return;
	}

	out.push_back("Greska! Nije pronadjen fajl sa imenom " + inputFile + '!');
}

// fileAccessException method definition
void ExceptionHandler::fileAccessException(string line, vector<string>& out) {
	string commandName;
	string option;
	string argument;
	TextHandler& textHandler = TextHandler::getInstance();

	textHandler.splitCommandParts(line, commandName, option, argument);

	string inputFile;
	string destinationFile;
	string arg;
	string method;

	textHandler.splitArgumentParts(argument, arg, inputFile, destinationFile, method);

	out.push_back("Greska pri otvaranju fajla sa imenom " + inputFile + '!');
}

// point method definition
void ExceptionHandler::point(string line, vector<string>& out, size_t pos) {
	Interpreter& interpreter = Interpreter::getInstance();
	line = interpreter.getReadySign() + ' ' + line;
	out.push_back(line);
	string pointer = "";
	for (size_t i = 0; i < pos + 2; i++) {
		if (line[i] == ' ' || line[i] == '\t') {
			pointer += line[i];
			continue;
		}
		pointer += ' ';
	}
	pointer += '^';
	out.push_back(pointer);
}

// belongsTo method definition
bool ExceptionHandler::belongsTo(string source, string target, char ch, size_t pos) {
	if (target.empty()) return false;
	size_t posInTarget = target.find(ch);
	if (posInTarget == string::npos) {
		return false;
	}

	size_t posOfTarget = source.find(target);
	if (pos < posOfTarget || pos > posOfTarget + target.size()) {
		return false;
	}
	
	return true;
}

ExceptionHandler::ExceptionHandler() {}