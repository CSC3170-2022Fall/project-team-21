#include <string>
#include <vector>
#include "Row.h"
#include "SchemaItem.h"
#include "Table.h"

using namespace std;

// This represents a single table in the database.
// It contains a schema and a list of rows.

// Create a new empty table with the name "default"
Table::Table(){

}

// need to restore the table from file with the name `name`
// you need to call `loadfromfile` to restore the table
Table::Table(std::string name, std::vector<SchemaItem> schema){
     //
}

// please refer to the format how mysql prints out the table
void  Table::printOut(){
     //
}

// use ofstream to store 
// first line is the schema
// then each line is a row
void Table::saveToFile(std::string fileName){
    // well, just find a way to make the database name as a directory,
    // and store the table in the directory
   string path = this->database->name + "/" + this->name + ".txt";
}

// Please refer to how to use std::vector
Row Table::getRowAt(int idx){
    //
}
void Table::removeRowAt(int idx){
    //
}

void Table::insertAt(Row row, int idx){
   
}
    

int Table::getSize(){
    return this->rows.size();
} 

Table Table::loadFromFile(std::string fileName){
    // Find a way to do this

}


std::string Table::getSchema() {
    std::string schema = "";
    string delimiter = " ";
    for (int i = 0; i < this->schema.size(); i++) {
        schema += this->schema[i].name + delimiter + this->schema[i].getType();
        if (i != this->schema.size() - 1) {
            schema += ", ";
        }
    }
    return schema;
}



