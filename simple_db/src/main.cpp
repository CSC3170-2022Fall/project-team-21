
#include <iostream>
#include <string>
#include "Table.h"
#include "CommandInterpreter.h"
#include "Database.h"

using namespace std;

// This is the driver function for our DB
int main()
{
    CommandInterpreter interpreter;
    Database db("db", &interpreter);
    printf("Welcome to Team 21's DB! Type SQL commands or 'help' or 'h' to get help, 'quit' or 'q' to exit\n");
    printf("Note: All SQL commands should end with a semicolon (;)\n");

    while (true)
    {
        printf("> ");
        string command;
        getline(cin, command);

        // allow these simple commands to not have a semicolon
        if (command == "quit" || command == "exit" || command == "h" || command == "help" || command == "q")
        {
            db.execute(string(command));
            continue;
        }
        while (true)
        {
            if (command.find(';') != string::npos)
            {
                command = command.substr(0, command.find(';'));
                break;
            }
            printf("> ");
            fflush(stdout);
            string temp;
            getline(cin, temp);
            command += " " + temp;
        }
        db.execute(command);
    }

    return 0;
}
