#include "Interpreter.h"
#include "IOHandler.h"
#include "TextHandler.h"
#include "Pipe.h"
#include "ExceptionHandler.h"

using namespace std;

// Main program
int main() {

    // Gets all nessecary instances
    Interpreter& interpreter = Interpreter::getInstance();

    IOHandler& readerAndWriter = IOHandler::getInstance();

    TextHandler& textHandler = TextHandler::getInstance();

    string input;

    while (true) {
        // Prints ready sign
        cout << interpreter.getReadySign() << " ";

        // One line is read
        input = readerAndWriter.readLine();

        // If line is empty, all after this is skipped
        if (input.empty()) continue;

        // If input is exit or EOF, program is stopped
        if (cin.eof() || input == "exit") {
            break;
        }

        // Commands vector, split commands
        vector<string> commands = textHandler.separateCommands(input);

        // Output vector
        vector<string> output;

        // If there is 1 command, interpret is called
        if (commands.size() == 1) {
            interpreter.interpret(input, output);
        }
        // If there is more commands, pipe execute is called
        else {
            Pipe pipe;
            output = pipe.execute(commands);
        }

        // print method is called to print output to console
        readerAndWriter.printOutput(output);
    }

    return 0;
}