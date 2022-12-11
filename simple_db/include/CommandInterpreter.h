
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
    Database *database;

    CommandInterpreter();

    void execute(std::string command, Database *db);

    // recursive function
    Table parse(std::string command);

    void createTable(std::vector<std::string> *v_command);
    void exitCommand();
    void load(std::vector<std::string> v_command);
    void printTable(std::vector<std::string> *v_command);
    Table select(std::vector<std::string> v_command);
    void insertCommand(std::vector<std::string> *v_command);
    // .... more. This file is harder than others.
    void guessUserInput(std::vector<std::string> v_command);
    void Spelling_error_correction(std::vector<std::string> *v_command);
    int lcs(std::string a, std::string b);

    Table naturalInnerProduct(std::string tableName1, std::string tableName2);
    bool testCondition(std::vector<SchemaItem> schema ,Row theRow, std::vector<std::string> conditionVector);


private:
    // split the command into tokens for better processing
    std::vector<std::string> command_tokens;

    std::vector<std::string> tokenizer(std::string str);
};
