
#pragma once

#include <string>
#include <vector>
#include "Table.h"
#include "Database.h"

class Table;
class Database;


class CommandInterpreter
{
private:
    // split the command into tokens for better processing
    std::vector<std::string> command_tokens;
    

    



public:
    CommandInterpreter();

    void execute(std::string command, Database *db, Table *table);

    // recursive function
    Table parse(std::string command);

    void createTable();
    void exit();
    void printTable();
    void select();
    // .... more. This file is harder than others.
};

