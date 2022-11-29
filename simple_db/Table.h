
#pragma once

#include <string>
#include <vector>
#include <Row.h>
#include <SchemaItem.h>

class Table
{
public:
    std::vector<Row> rows;
    std::vector<SchemaItem> schema;    

    // Create a table with the given name and columns
    Table(std::string name, std::vector<SchemaItem> schema);

    // Function to pretty-print the table in the console
    void printOut();
    void saveToFile(std::string fileName);
    Row getRowAt(int idx);
    void removeRowAt(int idx);
    // insert new row
    void insert(Row);
    int getSize();  // just return the size of the rows vector

    static Table loadFromFile(std::string fileName);

private:
    std::string name;
    void printHeader();

};

