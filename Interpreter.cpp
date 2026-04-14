#include "Interpreter.h"
#include "Translator.h"
#include "CommandFactory.h"
#include "ExceptionHandler.h"

// Returns instance of single object
Interpreter& Interpreter::getInstance() {
    static Interpreter instance;
    return instance;
}

// interpret method definition, it does everything about executing command
void Interpreter::interpret(string input, vector<string>& output) {
    string commandName;
    string option;
    string argument;

    Translator& translator = Translator::getInstance();
    TextHandler& textHandler = TextHandler::getInstance();
    ExceptionHandler& exceptionHandler = ExceptionHandler::getInstance();
    CommandFactory& commandFactory = CommandFactory::getInstance();

    // Vector out is for one command, and output is for whole output, if interpret was called multiple times before printing
    vector<string> out;
    bool toPrint = 0;

    bool status = exceptionHandler.checkForInvalidCharacters(input, output);

    // If status is false, that means that there was invalid character somewhere
    if (status) {
        try {
            // Command parts are separated
            textHandler.splitCommandParts(input, commandName, option, argument);

            // commandName is translated to Cmd
            Cmd name = translator.stringToCommand(commandName);

            // Command is created
            Command* command = commandFactory.createCommand(name, option, argument);

            // If command was succesfully created, execute method is called
            if (command) {
                command->execute(out, toPrint);
            }

            // If toPrint is 1, that means output didn't get redirected, and if it is 0, output was redirected to file
            if (toPrint == 1) {
                for (int i = 0; i < out.size(); i++) {
                    output.push_back(out[i]);
                }
            }

            // After usage, command gets deleted
            delete command;
        }
        // If exception occures, it gets caught in this block and gets processed further
        catch (Exception e) {
            exceptionHandler.handle(e, input, output);
        }
    }
}

// getReadySign method definition
string Interpreter::getReadySign() {
    return readySign;
}

// setReadySign method definition
void Interpreter::setReadySign(string newSign) {
    this->readySign = newSign;
}

Interpreter::Interpreter() {}