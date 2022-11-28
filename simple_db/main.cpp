
#include <iostream>
#include <string>

using namespace std;

// This is the driver function for our DB
int main() {
    while (true)
    {
        printf("Welcome to Team 21's DB! Type SQL commands or 'help' to get help, 'quit' to exit\n");
        printf("> ");
        string command;
        cin >> command;
        if (command == "exit" || command == "q" || command == "quit")
        {
            break;
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
            cout << "unrecognized command " << command << endl;
        }
    }
    
    return 0;
}
