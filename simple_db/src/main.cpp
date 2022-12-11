
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
    Database db(&interpreter);
    printf("Welcome to Team 21's DB! Type SQL commands or 'help' or 'h' to get help, 'quit' or 'exit' to exit\n");

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
