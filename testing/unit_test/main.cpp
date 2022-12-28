#include <iostream>
// #include "CommandInterpreter.h"
// #include "Conditions.h"
// #include "SchemaItem.h"
// #include "Table.h"

#include "Row_test.h"
#include "Schemaitem_test.h"
#include "Table_test.h"
#include "Database_test.h"
#include "test.h"

int main()
{
    std::cout << green << "RUNNING UNIT TEST FOR SIMPLE DATABASE" << std::endl;

    row_test::row_test();
    schemaitem_test::schemaitem_test();
    table_test::table_test();
    database_test::database_test();
}