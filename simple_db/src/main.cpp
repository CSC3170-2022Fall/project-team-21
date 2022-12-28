
#include <iostream>
#include <string>
#include "Table.h"
#include "CommandInterpreter.h"
#include "Database.h"

// This is the driver function for our DB
int main()
{
    CommandInterpreter interpreter;
    Database db("db", &interpreter);

    printf("Welcome to Team 21's DB! Type SQL commands or 'help' or 'h' to get help, 'quit' or 'q' to exit\n");
    printf("Note: All SQL commands should end with a semicolon (;)\n");

    db.start();

    return 0;
}
