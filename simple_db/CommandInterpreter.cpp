#include <iostream>
#include <string>
#include <vector>
#include "CommandInterpreter.h"


CommandInterpreter::CommandInterpreter(){}


void CommandInterpreter::execute(std::string command, Database *db, Table *table){
      // first convert command to all lowerspace
      // TODO: write this
      command = command.tolowercase();
      // then split the command into tokens by whitespace
      // like in python, string.split(" ")
      // please make it work for any number of whitespace
      //for better processing

      // we assume that each command should be a full command
      // not partial command
      //
      // a ";" in the end is ok, but not required

      if (this->command_tokens[0] == "select")
      {
            // first find the index of "from"
            int idx_of_from;
            parse(command[idx_of_from:])  // TODO
      }
      

      //fill in
      // invoke the corresponding function based on the first token
      // if the first token is "create", invoke createTable()
      // if the first token is "exit", invoke exit()
      // if the first token is "print", invoke printTable()
      // if the first token is "select", invoke select()
      // .... more
      if (command == "exit" || command == "q" || command == "quit")
        {
            printf("exit");
        }
        else if (command == "insert")
        {
            printf("inserting...\n");
        }
        else if (command == "select")
        {
            printf("selecting...\n");
        }
        else if (command == "help")
        {
            printf("Help message here\n");
        }
        else
        {
            printf("unrecognized command\n ");
            //cout << "unrecognized command " << command << endl;
        }

}

// should use each function for one type of command
void CommandInterpreter::createTable(){
      //fill in

}
void CommandInterpreter::exit(){
      //fill in

}

void CommandInterpreter::printTable(){
      //fill in

}
void CommandInterpreter::select(){
      //fill in

}


