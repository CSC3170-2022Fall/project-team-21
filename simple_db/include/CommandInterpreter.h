
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

    void execute(std::vector<std::string> v_command, Database *db);
    bool getInputCommand(std::vector<std::string> &v_command, bool command_continue);

    // recursive function

    void createTable(std::vector<std::string> *v_command);
    void deleteTable(std::vector<std::string> *v_command);
    void deleteRow(std::vector<std::string> v_command);
    void exitCommand();
    void load(std::vector<std::string> v_command);
    void store(std::vector<std::string> *v_command);
    void printTable(std::vector<std::string> *v_command);
    Table select(std::vector<std::string> v_command);
    void insertCommand(std::vector<std::string> *v_command);
    // .... more. This file is harder than others.
    //void guessUserInput(std::vector<std::string> v_command);
    void spellingErrorCorrection(std::vector<std::string> *v_command);
    int lcs(std::string a, std::string b);
    int findTable(std::string tableName);
    int judgeSelect(std::vector<std::string> v_command);

    Table naturalInnerProduct(std::string tableName1, std::string tableName2);
    bool testCondition(std::vector<SchemaItem> schema ,Row theRow, std::vector<std::string> conditionVector);

    std::vector<std::string> tokenizer(std::string str);

private:
    // split the command into tokens for better processing
    std::vector<std::string> command_tokens;

};
