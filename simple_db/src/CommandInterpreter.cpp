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

      // we assume that each command should be a full command
      // not partial command
      //
      // a ";" in the end is ok, but not required

      if (this->command_tokens[0] == "select")
      {
            // first find the index of "from"
            int idx_of_from;
            // parse(command[idx_of_from:])  // TODO
      }
      else if (v_command[0] == "exit" || v_command[0] == "q" || v_command[0] == "quit")
      {
          // first save to file, then return
          return;
      }
      else if (v_command[0] == "insert")
      {
        // call the insert handler
          printf("inserting...\n");
      }
      else if (v_command[0] == "help")
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
// please add the parameters as you want, maybe the Database object pointer
void CommandInterpreter::createTable(){
      //fill in

}
void CommandInterpreter::exit(){
      //fill in

}

void CommandInterpreter::printTable(){
      //fill in

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
