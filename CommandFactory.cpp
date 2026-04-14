#include "CommandFactory.h"

// Returns instance of single object
CommandFactory& CommandFactory::getInstance() {
    static CommandFactory instance;
    return instance;
}

// createCommand method definition
Command* CommandFactory::createCommand(Cmd name, string option, string argument) {

    // Calls the command constructor depending on the command
    switch (name) {
        case echo: return new EchoCommand(option, argument); break;
        case date: return new DateCommand(option, argument); break;
        case timeCmd: return new TimeCommand(option, argument); break;
        case touch: return new TouchCommand(option, argument); break;
        case wc: return new WcCommand(option, argument); break;
        case prompt: return new PromptCommand(option, argument); break;
        case truncate: return new TruncateCommand(option, argument); break;
        case rm: return new RmCommand(option, argument); break;
        case tr: return new TrCommand(option, argument); break;
        case head: return new HeadCommand(option, argument); break;
        case batch: return new BatchCommand(option, argument); break;
    }
}

CommandFactory::CommandFactory() {}