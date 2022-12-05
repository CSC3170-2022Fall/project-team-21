
#pragma once

#include <string>
#include <vector>
#include "Table.h"
#include "CommandInterpreter.h"
 
class Database {
    private:
        // tables in this database
        std::vector<Table> tables;

        // the table that is currently being worked on
        Table* currentTable;

        CommandInterpreter *interpreter;



    public:
        std::string name;
        // Create a database with the given name
        // restore all tables from files
        // maybe could **postfix or prefix the file name with the database name** to distinguish which database the table belongs
        
        Database(CommandInterpreter *interpreter);
        Database(std::string name, CommandInterpreter *interpreter);

        Table* getTable(std::string tableName);

        // switch the current table to the given table
        void switchTable(std::string tableName);

        void addTable(Table table);
        

        // remove a table from the database
        void removeTable(std::string tableName);
        void removeTableAtIdx(int idx);


        // just call the CommandInterpreter, groupmates can implement this
        void execute(std::string command);

        // save each table to a file
        // by repeatedly calling the save on each of tables
        void saveDatabase();
};