
#pragma once

#include <string>
#include <vector>
#include "Row.h"
#include "SchemaItem.h"
#include "Database.h"

class Table
{
public:
    std::vector<Row> rows;
    std::vector<SchemaItem> schema;   
    Database *database; // the db it belongs to

    // Create a table with the given name and columns
    Table();
    Table(std::string name, std::vector<SchemaItem> schema);

    // Function to pretty-print the table in the console
    void printOut();
    void saveToFile(std::string fileName);
    Row getRowAt(int idx);
    void removeRowAt(int idx);
    // insert new row
    void insertAt(Row row, int idx);
    int getSize();  // just return the size of the rows vector

    static Table loadFromFile(std::string fileName);

private:
    std::string name;
    std::string getSchema();

};

