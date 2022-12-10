#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "CommandInterpreter.h"
#include <algorithm>

using namespace std;

CommandInterpreter::CommandInterpreter(){
}


void CommandInterpreter::execute(std::string command, Database *db){
      // split the command into tokens by whitespace
      // like in python, string.split(" ")
      // please make it work for any number of whitespace
      //for better processing
      std::vector<std::string> v_command = tokenizer(command);


      if (v_command[0] == "select")
      {
            // first find the index of "from"
            int idx_of_from;
            // parse(command[idx_of_from:])  // TODO
      }
      else if (v_command[0] == "create" && v_command[1] == "table")
      {
            // call the create table handler
            createTable(&v_command);
      }
      else if (v_command[0] == "exit" || v_command[0] == "q" || v_command[0] == "quit")
      {
          // first save to file, then return
          exitCommand();
      }
      else if (v_command[0] == "insert" && v_command[1] == "into")
      {
        // call the insert handler
        insertCommand(&v_command);
      }
      else if(v_command[0] == "load")
      {
            this->load(v_command);
      }
      else if (v_command[0] == "print")
      {
            printTable(&v_command);
      }
      else if (v_command[0] == "help")
      {
          printf("Help message here\n");
      }
      else
      {
          printf("Invalid command, please try again.\n");
      }

}

void CommandInterpreter::insertCommand(std::vector<std::string> *v_command){
      // insert to <table_name> values <value1>, <value2>, ...
      string tableName = v_command->at(2);
      // if tablename contains brackets, ignore them
      if(tableName[tableName.length()-1] == ')'){
            tableName = tableName.substr(0, tableName.find_first_of('('));
      }
      Table *target_table = this->database->getTable(tableName);

      vector<string> values;
      for(int i = 4; i < v_command->size(); i++){
            values.push_back(v_command->at(i));
      }
      Row newRow = Row(values);
      target_table->insertLast(newRow);
}

// should use each function for one type of command
// please add the parameters as you want, maybe the Database object pointer
void CommandInterpreter::createTable(std::vector<std::string> *v_command){
      string tableName = v_command->at(2);
      vector<SchemaItem> schema;

      int i = 4;
      while (i < v_command->size()) {
            string schemaItem = v_command->at(i);
            DataType schemaType;
            string schemaName;
            // if schemaItem contains brackets
            if(schemaItem[schemaItem.length()-1] == ')'){
                  schemaName = schemaItem.substr(0, schemaItem.find('('));
                schemaType = SchemaItem::getTypeFromString(schemaItem.substr(
                  schemaItem.find('(')+1, schemaItem.find(')') - schemaItem.find('(') - 1
                ));
            } else {
                schemaType = SchemaItem::getTypeFromString(
                  v_command->at(++i)
                );
                schemaName = schemaItem;
            }
            SchemaItem newSchemaItem = SchemaItem();
            newSchemaItem.name = schemaName;
            newSchemaItem.type = schemaType;
            schema.push_back(newSchemaItem);
            i++;
      }

}
void CommandInterpreter::exitCommand(){
      cout << "Bye!" << endl;
      exit(0);
}

void CommandInterpreter::load(std::vector<std::string> v_command){
      string tableName;
      tableName = v_command[1].substr(0, v_command[1].length()-1);
      Table tableTemp;
      tableTemp = tableTemp.loadFromFile(tableName, this->database->name);
      this->database->addTable(tableTemp);
      cout << "Successfully loaded table: " << v_command[1] << endl;
}


void CommandInterpreter::printTable(std::vector<std::string> *v_command){
      string target_table_name = v_command->at(1);
      Table *target_table = this->database->getTable(target_table_name);
      target_table->printOut();
}
Table CommandInterpreter::select(){
      //fill in

}

// Segment string into tokens, split by " "
std::vector<std::string> CommandInterpreter::tokenizer(std::string str)
{
    std::stringstream ss(str);
    std::vector<std::string> tokens;
    std::string word;
    while (ss >> word)
    {
        // convert word to lowercase
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        tokens.push_back(word);
    }
    ss.clear();
    return (tokens);
}
