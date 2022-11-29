
#pragma once

#include <string>
#include <vector>
#include <Table.h>

 
class Database {
    private:
        std::string name;
        std::vector<Table> tables;
        Table voidTable;

        // remove a table from the database
        void removeTable(std::string tableName);



    public:
        // Create a database with the given name
        // restore all tables from files
        // maybe could **postfix or prefix the file name with the database name** to distinguish which database the table belongs
        
        Database();
        Database(std::string name);

        // execute a query, returns the result table
        // some commands don't return a table, in that case, return a void table
        Table execute(std::string command);

        // save each table to a file
        void saveDatabase();
        // save the schema to a file
        void saveSchema();
};