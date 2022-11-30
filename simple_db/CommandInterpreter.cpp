#include <iostream>
#include <string>
#include <vector>
#include "CommandInterpreter.h"


CommandInterpreter::CommandInterpreter(){
      //fill in
      // split the command into tokens by whitespace
      // like in python, string.split(" ")
      // please make it work for any number of whitespace
      //for better processing

      // we assume that each command should be a full command
      // not partial command
      //
      // a ";" in the end is ok, but not required

}

void CommandInterpreter::execute(std::string command){
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


