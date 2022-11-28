
#pragma once

#include <string>
#include <vector>

class CommandInterpreter
{
private:
    // split the command into tokens for better processing
    std::vector<std::string> command_tokens;
public:
    CommandInterpreter(std::string command);

    void createTable();
    void exit();
    void printTable();
    void select();
    // .... more. This file is harder than others.
};

