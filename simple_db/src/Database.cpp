#include <iostream>
#include <string>
#include <vector>
#include "Table.h"
#include "Database.h"
#include "CommandInterpreter.h"
#include <direct.h>
//#include <stdlib.h>
//#include <stdio.h>

Database::Database(CommandInterpreter *interpreter){
    this->interpreter = interpreter;
    this->name = "default";
}

Database::Database(std::string name, CommandInterpreter *interpreter){
    this->name = name;
    this->interpreter = interpreter;
}

void Database::execute(std::string command){
    this->interpreter->execute(command, this, this->currentTable);
}


void Database::saveDatabase(){
    // TODO: first create the directory for the database,
    // then **change directory** to it
    const char * nm = this->name.c_str();
     if( _mkdir(strcat("\\",nm)) == 0 )
   {
      printf("Directory '\\%c' was successfully created\n",*nm );
      //system( "dir \\"+ this->name );
      for (int i = 0; i < this->tables.size(); i++)
    {
        std::string fname = this->tables[i].name;
        this->tables[i].saveToFile(fname);
    }
   }
   else
      printf( "Problem creating directory '\\%c'\n",*nm );


    
    
}

Table* Database::getTable(std::string tableName){
    // TODO
    int idx = -1;

    for (int i = 0; i < this->tables.size(); i++)
    {
        if(this->tables[i].name == tableName){
            idx = i;
        }
    }
    return &this->tables[idx];
}
void Database::switchTable(std::string tableName){
    int idx = -1;

    for (int i = 0; i < this->tables.size(); i++)
    {
        if(this->tables[i].name == tableName){
            idx = i;
        }
    }
    currentTable = &this->tables[idx];
}

void Database::addTable(Table table){
    this->tables.push_back(table);
    
}

void Database::removeTable(std::string tableName){
    int idx = -1;

    for (int i = 0; i < this->tables.size(); i++)
    {
        if(this->tables[i].name == tableName){
            idx = i;
        }
    }
    this->tables.erase(this->tables.begin()+idx);

}

void Database::removeTableAtIdx(int idx){

    this->tables.erase(this->tables.begin()+idx);
}