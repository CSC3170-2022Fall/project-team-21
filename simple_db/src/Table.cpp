#include <iostream>
#include <string>
#include <vector>
#include "Row.h"
#include "SchemaItem.h"
#include "Table.h"
#include <fstream>
#include <iomanip>

using namespace std;

// This represents a single table in the database.
// It contains a schema and a list of rows.

// Create a new empty table with the name "default"
Table::Table()
{
    this->name = "default";
}

// need to restore the table from file with the name `name`
// you need to call `loadfromfile` to restore the table
Table::Table(std::string name, std::vector<SchemaItem> schema)
{
    this->name = name;
    this->schema = schema;
    this->rows.clear();
}

// please refer to the format how mysql prints out the table
/*
we make it to be consistent with the table in the ucb project
*/
void Table::printOut()
{

    // pretty print the table using iomanip
    vector<int> colWidth;

    // set the width of each column by the length of the longest string in the column as well as the schema'
    for (int i = 0; i < this->schema.size(); i++)
    {
        int maxLength = this->schema[i].getName().length();
        for (int j = 0; j < this->rows.size(); j++)
        {
            if (this->rows[j].values[i].length() > maxLength)
            {
                maxLength = this->rows[j].values[i].length();
            }
        }
        colWidth.push_back(maxLength);
    }

    // print out the schema
    cout << "    ";
    for (int i = 0; i < this->schema.size(); i++)
    {
        cout << setw(colWidth[i]) << setfill(' ') << this->schema[i].getName() << "  ";
    }

    int total_width = 0;
    for (int i = 0; i < colWidth.size(); i++)
    {
        total_width += colWidth[i] + 2;
    }
    cout << '\n';
    cout << "    ";
    cout << setw(total_width) << setfill('-') << ' ';
    cout << '\n';

    // print out the row
    for (int i = 0; i < this->rows.size(); i++)
    {
        cout << "    ";
        std::vector<std::string> values = this->rows[i].getValues();
        for (int j = 0; j < values.size(); j++)
        {
            cout << setw(colWidth[j]) << setfill(' ') << values[j] << "  ";
        }
        cout << "\n";
    }
}

// use ofstream to store
// first line is the schema
// then each line is a row
void Table::saveToFile(std::string fileName)
{
    // well, just find a way to make the database name as a directory,
    // and store the table in the directory
    string path = "../../testing/database/" + this->database->name + "_" + this->name + ".db";

    ofstream onFile(path);

    for (int i = 0; i < this->schema.size() - 1; i++)
    {
        onFile << this->schema[i].name << ",";
    }
    onFile << this->schema[this->schema.size() - 1].name << endl;

    for (int i = 0; i < this->rows.size(); i++)
    {
        for (int j = 0; j < this->rows[i].values.size() - 1; j++)
        {
            onFile << this->rows[i].values[j] << ",";
        }
        onFile << this->rows[i].values[this->rows[i].values.size() - 1] << endl;
    }

    onFile.close();
}
// Please refer to how to use std::vector
Row Table::getRowAt(int idx)
{
    return this->rows.at(idx);
}
void Table::removeRowAt(int idx)
{
    this->rows.erase(this->rows.begin() + idx);
}

void Table::insertLast(Row row)
{
    this->rows.push_back(row);
}

void Table::insertAt(Row row, int idx)
{
    this->rows.insert(this->rows.begin() + idx, row);
}

int Table::getSize()
{
    return this->rows.size();
}

Table Table::loadFromFile(std::string tableName, std::string databaseName)
{
    // Find a way to do this
    string path = "../../testing/database/" + databaseName + "_" + tableName + ".db";
    ifstream inFile;
    inFile.open(path, ios::in);

    if (inFile.is_open() == false)
    {
        cout << "Error: File not found" << endl;
        return Table();
    }

    Table tableOut;
    tableOut.name = tableName;
    vector<Row> rows;

    vector<SchemaItem> schema;
    string stringIntoTable = "";
    char c;
    int line = 0;
    while ((c = inFile.get()) != EOF)
    {
        if (c == '\n')
        {
            if (line == 0)
            {
                SchemaItem item;
                item.name = stringIntoTable;
                item.type = DB_STRING;
                schema.push_back(item);
            }
            else
            {
                rows[line - 1].values.push_back(stringIntoTable);
            }
            vector<std::string> rowTemp;
            Row temp(rowTemp);
            rows.push_back(temp);
            stringIntoTable = "";
            line++;
            continue;
        }
        if (c == ',')
        {
            if (line == 0)
            {
                SchemaItem item;
                item.name = stringIntoTable;
                item.type = DB_STRING;
                schema.push_back(item);
            }
            else
            {
                rows[line - 1].values.push_back(stringIntoTable);
            }

            stringIntoTable = "";
            continue;
        }
        stringIntoTable += c;
    }

    rows.pop_back();
    tableOut.rows = rows;
    tableOut.schema = schema;

    inFile.close();

    printf("Loaded %s.db\n", tableName.c_str());

    return tableOut;
}

std::string Table::getSchema()
{
    std::string schema = "";
    string delimiter = " ";
    for (int i = 0; i < this->schema.size(); i++)
    {
        schema += this->schema[i].name + delimiter + this->schema[i].getType();
        if (i != this->schema.size() - 1)
        {
            schema += ", ";
        }
    }
    return schema;
}
