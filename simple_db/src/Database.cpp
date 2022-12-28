#include <iostream>
#include <string>
#include <vector>
#include "Table.h"
#include "Database.h"
#include "CommandInterpreter.h"

using namespace std;


Database::Database(CommandInterpreter *interpreter)
{
    this->interpreter = interpreter;
    this->interpreter->database = this;
    this->name = "default";
}

Database::Database(std::string name, CommandInterpreter *interpreter)
{
    this->name = name;
    this->interpreter = interpreter;
    this->interpreter->database = this;
}

void Database::start()
{
    vector<std::string> v_command;
    bool get_command = false;
    bool command_continue = false; // if input a command in more than one line

    while (true)
    {
        get_command = this->interpreter->getInputCommand(v_command, command_continue);
        if (get_command)
        {
            execute(v_command);
            v_command.clear();
        }
    }
}

void Database::execute(std::vector<std::string> v_command)
{
    this->interpreter->execute(v_command, this);
}

void Database::saveDatabase()
{

    string cmd = "mkdir " + this->name;
    system(cmd.c_str());
    string cmd2 = "cd " + this->name;
    system(cmd2.c_str());
    for (int i = 0; i < this->tables.size(); i++)
    {
        std::string fname = this->tables[i].name;
        this->tables[i].saveToFile(fname);
    }
    string cmd3 = "cd ..";
    system(cmd3.c_str());
}

Table *Database::getTable(std::string tableName)
{
    // TODO
    int idx = -1;

    for (int i = 0; i < this->tables.size(); i++)
    {
        if (this->tables[i].name == tableName)
        {
            idx = i;
        }
    }
    if (idx != -1)
    { // the table we search is found
        return &this->tables[idx];
    }
    else
    { // the table we search is not found
        return NULL;
    }
}

void Database::addTable(Table table)
{
    table.database = this;
    this->tables.push_back(table);
}

void Database::removeTable(std::string tableName)
{
    int idx = -1;

    for (int i = 0; i < this->tables.size(); i++)
    {
        if (this->tables[i].name == tableName)
        {
            idx = i;
        }
    }
    this->tables.erase(this->tables.begin() + idx);
}

void Database::removeTableAtIdx(int idx)
{

    this->tables.erase(this->tables.begin() + idx);
}