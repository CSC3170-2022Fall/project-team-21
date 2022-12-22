
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
    
    std::vector<std::string> v_command;

    printf("Welcome to Team 21's DB! Type SQL commands or 'help' or 'h' to get help, 'quit' or 'q' to exit\n");
    printf("Note: All SQL commands should end with a semicolon (;)\n");

    while (true)
    {
        v_command.clear();
        printf("> ");
        string command;
        getline(cin, command);

        // allow these simple commands to not have a semicolon
        if (command == "quit" || command == "exit" || command == "h" || command == "help" || command == "q")
        {
            v_command.push_back(command);
            db.execute(v_command);
            continue;
        }

        while (true)
        {
            if ((command[command.length() - 1] == '/' && command[command.length() - 2] == '*'))
            {
                break;
            }


            if (command.length() == 0)
            {
                break;
            }


            if (command.find(';') != string::npos)
            {
                command = command.substr(0, command.find(';'));

                break;
            }


            printf("You need to have a semicolumn(;) at the end of your input. Please input again.\n");
            printf("> ");
            fflush(stdout);

            string temp;
            getline(cin, temp);
            command += " " + temp;
        }

        db.execute(v_command);

    }

    return 0;
}
