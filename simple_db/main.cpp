
#include <iostream>
#include <string>
#include "CommandInterpreter.h"
#include "Database.h"

using namespace std;


// This is the driver function for our DB
int main() {
    CommandInterpreter interpreter;
    Database db(&interpreter);
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
        db.execute(command);
        
    }
    
    return 0;
}
