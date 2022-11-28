
#pragma once

#include <string>
#include <vector>
#include <Row.h>
#include <Col.h>

class Table
{
public:
    std::vector<Row> rows;
    // Create a table with the given name and columns
    Table(std::string name, std::vector<Col> columns);

    // Function to pretty-print the table in the console
    void printOut();
    void saveToFile(std::string fileName);
    Row getRowAt(int idx);
    void removeRowAt(int idx);
    // insert new row
    void insert(Row);

    static Table loadFromFile(std::string fileName);

private:
    std::vector<Col> columns;
    std::string name;
    void printHeader();

};

