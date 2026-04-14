#include "TextHandler.h"

// Returns instance of single object
TextHandler& TextHandler::getInstance() {
    static TextHandler instance;
    return instance;
}

// extractBetween method definition
string TextHandler::extractBetween(string text, char startChar, char endChar) {
    // Finds positions of given characters
    size_t startPos = text.find(startChar);
    size_t endPos = text.find(endChar, startPos + 1);
    
    // Calls extractBetweenPositions method
    return extractBetweenPositions(text, startPos, endPos);
}

// extractBetweenPositions method definition
string TextHandler::extractBetweenPositions(string text, size_t startPos, size_t endPos) {
    // Returns substring between two positions if positions are valid
    if (startPos != string::npos && endPos != string::npos && endPos > startPos) {
        return text.substr(startPos + 1, endPos - startPos - 1);
    }

    return "";
}

// replaceSubstring method
string TextHandler::replaceSubstring(string text, string what, string with) {
    size_t pos = 0;
    // Replaces substring with another text
    while ((pos = text.find(what, pos)) != string::npos) {
        text.replace(pos, what.length(), with);
        pos += with.length();
    }

    return text;
}

// separateCommands method definition, separates commands divided by |
vector<string> TextHandler::separateCommands(string line) {
    vector<string> commands;
    string current;
    bool insideQuotes = false;

    for (int i = 0; i < line.length(); ++i) {
        char c = line[i];

        if (c == '"') {
            insideQuotes = !insideQuotes;
            current += c;
        }
        else if (c == '|' && !insideQuotes) {
            size_t start = current.find_first_not_of(" \t");
            size_t end = current.find_last_not_of(" \t");
            if (start != string::npos)
                commands.push_back(current.substr(start, end - start + 1));
            else
                commands.push_back("");
            current.clear();
        }
        else {
            current += c;
        }
    }

    size_t start = current.find_first_not_of(" \t");
    size_t end = current.find_last_not_of(" \t");
    if (start != std::string::npos)
        commands.push_back(current.substr(start, end - start + 1));
    else
        commands.push_back("");

    return commands;
}

// splitArgumentParts method definition, splits parts of an argument, input file, output file, method, and argument inside quotes
void TextHandler::splitArgumentParts(string& text, string& argument, string& sourceFile, string& destinationFile, string& method) {
    if (count(text.begin(), text.end(), '"') >= 2) {
        size_t firstQuote = text.find('"');
        size_t lastQuote = text.rfind('"');
        argument = '"' + extractBetweenPositions(text, firstQuote, lastQuote) + '"';
        text.erase(firstQuote, lastQuote - firstQuote + 1);
        while (!text.empty() && text.front() == ' ') {
            text.erase(0, 1);
        }
        if (argument.size() == 2) {
            argument.clear();
        }
    }
    
    size_t pos;
    if ((pos = text.find('<')) != string::npos) {
        size_t start = pos + 1;
        while (start < text.size() && text[start] == ' ') {
            start++;
        }
        size_t end = text.find(' ', start);
        sourceFile = text.substr(start, end - start);
        text.erase(pos, (end == string::npos ? text.size() : end) - pos);
    }

    if ((pos = text.find(">")) != string::npos) {
        size_t start = pos;
        method = ">";
        if (start + 1 < text.size() && text[start + 1] == '>') {
            start++;
            method += ">";
        }
        start++;

        while (start < text.size() && text[start] == ' ') {
            start++;
        }
        size_t end = text.find(' ', start);
        destinationFile = text.substr(start, end - start);
        text.erase(pos, (end == string::npos ? text.size() : end) - pos);
    }

    // If input file wasn't given by redirection, it is maybe given normal, but redirection has priority
    if (sourceFile.empty()) {
        string leftover = text;
        while (!leftover.empty() && (leftover.front() == ' ' || leftover.front() == '\t')) {
            leftover.erase(0, 1);
        }
        if (!leftover.empty()) {
            sourceFile = leftover;
            text.clear();
            while (!sourceFile.empty() && (sourceFile.back() == ' ' || sourceFile.back() == '\t')) {
                sourceFile.pop_back();
            }
        }
    }
    while (!text.empty() && (text.front() == ' ' || text.front() == '\t')) {
        text.erase(0, 1);
    }
    while (!text.empty() && (text.back() == ' ' || text.back() == '\t')) {
        text.pop_back();
    }
}

// splitCommandParts metdhod definition, separates command name, option and argument
void TextHandler::splitCommandParts(string line, string& name, string& option, string& argument) {
    while (!line.empty() && (line.front() == ' ' || line.front() == '\t')) {
        line.erase(0, 1);
    }
    istringstream iss(line);

    iss >> name;

    if (iss >> option) {
        if (option[0] != '-') {
            argument = line;

            // Argument is whole line with deleted command name and option
            argument.erase(0, name.size());
            while (argument.front() == ' ' || argument.front() == '\t') {
                argument.erase(0, 1);
            }
            option = "";

        }

        // If option exists, argument is what is left in string
        else {
            argument = line;

            // Argument is whole line with deleted command name and option
            argument.erase(0, name.size() + option.size() + 2);
            while (!argument.empty() && (argument.front() == ' ' || argument.front() == '\t')) {
                argument.erase(0, 1);
            }

        }
    }
}

TextHandler::TextHandler() {}