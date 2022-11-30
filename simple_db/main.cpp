
#include <iostream>
#include <string>
#include "CommandInterpreter.h"
#include "Database.h"
// please include the header files you need to drive this program

using namespace std;


// This is the driver function for our DB
int main() {
    Database db;
    CommandInterpreter interpreter;
    printf("Welcome to Team 21's DB! Type SQL commands or 'help' to get help, 'quit' to exit\n");
    
    while (true)
    {
        printf("> ");
        string command;
        cin >> command;
        while (command.find(';') == string::npos)
        {
            string temp;
            cin >> temp;
            command += " " + temp;
        }
        interpreter.execute(command);
        
    }
    
    return 0;
}
