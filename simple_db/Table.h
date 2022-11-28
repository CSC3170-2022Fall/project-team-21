
#pragma once

#include <string>
#include <vector>
#include <Row.h>
#include <Col.h>

class Table
{
public:
    // Create a table with the given name and columns
    Table(std::string name, std::vector<Col> columns);

    // Function to pretty-print the table in the console
    void printOut();
    void saveToFile(std::string fileName);

    static Table loadFromFile(std::string fileName);

private:
    std::vector<Row> rows;
    std::vector<Col> columns;
    std::string name;
    void printHeader();

};

