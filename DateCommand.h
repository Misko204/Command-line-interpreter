#ifndef DATECOMMAND_H
#define DATECOMMAND_H

#include "Command.h"

// Date command, inherits class Command
class DateCommand : public Command {
public:

    // Constructor
    DateCommand(string option, string argument);

    // execute method
    void execute(vector<string>& out, bool& toPrint) override;

    // perform method
    void perform(vector<string>& args) override;

};

#endif