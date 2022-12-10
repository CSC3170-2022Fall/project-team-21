
#pragma once

#include <string>
#include <vector>
#include "Table.h"
#include "Database.h"

class Table;
class Database;


class CommandInterpreter
{


public:
    CommandInterpreter();

    void execute(std::string command, Database *db);

    // recursive function
    Table parse(std::string command);

    void createTable();
    void exit();
    void printTable();
    Table select();
    // .... more. This file is harder than others.

private:
    // split the command into tokens for better processing
    std::vector<std::string> command_tokens;
    
    std::vector<std::string> tokenizer(std::string str);

    Database * database;


};

