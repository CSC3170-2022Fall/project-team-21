#include <string>
#include <vector>
#include "Row.h"
#include "SchemaItem.h"
#include "Table.h"

Table::Table(){

}
Table::Table(std::string name, std::vector<SchemaItem> schema){
     //
}


void  Table::printOut(){
     //
}
void Table::saveToFile(std::string fileName){
     //
}
Row Table::getRowAt(int idx){
    //
}
void Table::removeRowAt(int idx){
    //
}

void Table::insert(Row){
     //
}
int Table::getSize(){
    //
} 

Table Table::loadFromFile(std::string fileName){
    //
}


void Table::printHeader(){
    //
}



