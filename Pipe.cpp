#include "Pipe.h"

// execute method definition
vector<string> Pipe::execute(vector<string> commands){

    Translator& translator = Translator::getInstance();
    CommandFactory& commandFactory = CommandFactory::getInstance();
    TextHandler& textHandler = TextHandler::getInstance();
    FileHandler& fileHandler = FileHandler::getInstance();
    ExceptionHandler& exceptionHandler = ExceptionHandler::getInstance();

    vector<string> result;
    bool toPrint = 0;

    // Commands are separated, every command is handeled by itself
    for (int i = 0; i < commands.size(); i++) {
        string commandName;
        string option;
        string argument;
        string input = commands[i];

        bool status = exceptionHandler.checkForInvalidCharacters(input, result);

        // If status is false that means there is invalid character somewhere
        if (!status) {
            string point = result.back();
            string line = result[result.size() - 2];
            result.clear();
            result.push_back(line);
            result.push_back(point);
            break;
        }

        try {
            // Command parts are separated
            textHandler.splitCommandParts(input, commandName, option, argument);

            Cmd name = translator.stringToCommand(commandName);

            Command* command = commandFactory.createCommand(name, option, argument);

            if (!command) {
                result.clear();
                return result;
            }

            string inputFile;
            string destinationFile;
            string method;
            argument.clear();

            string rest = command->getArg();

            textHandler.splitArgumentParts(rest, argument, inputFile, destinationFile, method);
            
            // In this part program checks for exceptions and handles first argument
            if ((commandName == "date" || commandName == "time") && (!inputFile.empty() || !result.empty() || !argument.empty())) {
                size_t inputPos = string::npos;
                if (!inputFile.empty()) inputPos = input.find(inputFile);
                size_t argPos = string::npos;
                if (!argument.empty()) argPos = input.find(argument);
                if (inputPos < argPos) {
                    throw InputFileNotExpected;
                }
                else {
                    throw NoArgumentExpected;
                }
            }
            else if (commandName != "date" && commandName != "time" && inputFile.empty() && argument.empty() && i == 0) {
                throw ArgumentMissing;
            }
            else if (!inputFile.empty() && !argument.empty() && i == 0) {
                size_t InputPos = input.find(inputFile);
                size_t argPos = input.find(argument);
                if (argPos > InputPos) {
                    throw InputFileNotExpected;
                }
                throw NoArgumentExpected;
            }
            else if (!inputFile.empty() && argument.empty() && i == 0) {
                result = fileHandler.readFromFile(inputFile);
            }
            else if (inputFile.empty() && !argument.empty() && i == 0) {
                if (name == tr) {
                    string rest = argument;
                    argument = textHandler.extractBetween(argument, '"', '"');
                    rest.erase(0, argument.size() + 2);
                    result.push_back(argument);
                    if (!rest.empty()) {
                        result.push_back(rest);
                    }
                }
                else {
                    size_t firstQuote = argument.find('"');
                    size_t lastQuote = argument.rfind('"');
                    argument = textHandler.extractBetween(argument, '"', '"');
                    result.push_back(argument);
                }
            }
            else if (!argument.empty() && i != 0) {
                if (commandName == "tr") result.push_back(argument);
                else throw NoArgumentExpected;
            }
            else if (!inputFile.empty() && i != 0) {
                throw InputFileNotExpected;
            }
            if (command->getOption().empty() && (commandName == "wc" || commandName == "head")) {
                throw OptionMissing;
            }
            else if (!command->getOption().empty()) {
                string opt = command->getOption();
                if (commandName != "head" && commandName != "wc") {
                    throw NoOptionExpected;
                }
                else if (commandName == "wc" && (opt == "-w" || opt == "-c")) {
                    result.push_back(command->getOption());
                }
                else if (commandName == "head" && (opt.substr(0, 2) == "-n" && stoll(opt.substr(2)) <= 99999)) {
                    result.push_back(command->getOption());
                }
                else {
                    throw UnknownOption;
                }
                
            }

            // For every command perform method is called
            command->perform(result);

            toPrint = 1;

            // If destination file is not empty, output is redirected there
            if (!destinationFile.empty() && i == commands.size() - 1) {
                command->redirectTo(result, destinationFile, method);
                result.clear();
                result.push_back(destinationFile);
                toPrint = 0;
            }

            delete command;
        }
        catch (Exception exception) {
            result.clear();
            exceptionHandler.handle(exception, input, result);
            toPrint = 1;
            break;
        }
    }

    if (toPrint == 0) {
        result.clear();
    }
    
    return result;
}