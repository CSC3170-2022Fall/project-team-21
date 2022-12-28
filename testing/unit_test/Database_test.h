#pragma once

// test Table class

#include <iostream>
#include <vector>
#include <string>
#include "Table.h"
#include "SchemaItem.h"
#include "CommandInterpreter.h"
#include "Row.h"
#include "test.h"

namespace database_test
{

    // prepare for the test case
    std::vector<SchemaItem> prepare_schema(std::vector<std::string> name, std::vector<std::string> type)
    {
        // schema
        std::vector<SchemaItem> schema;

        for (int i = 0; i < 3; ++i)
        {
            SchemaItem new_schema_item = SchemaItem(name[i], SchemaItem::getTypeFromString(type[i]));
            schema.push_back(new_schema_item);
        }

        return schema;
    }

    std::vector<Row> prepare_rows(std::vector<Row> rows, std::vector<std::string> new_value)
    {
        Row new_row = Row(new_value);
        rows.push_back(new_row);
        return rows;
    }

    void check_addTable(Database &db, Table table, bool verbose)
    {
        db.addTable(table);
        Table* check_table = db.getTable(table.name);
        if (verbose)
        {
            std::cout << "------------------" << std::endl;
            std::cout << "the table added: " << table.name << std::endl;
            check_table->printOut();
        }
    }

    void check_removeTableAtIdx(Database &db, int idx)
    {

        std::cout << "------------------" << std::endl;
        std::cout << "Before removing: Number of tables in database: " << std::to_string(db.tables.size()) << std::endl;
        std::cout << "Remove table at index: " << std::to_string(idx) << std::endl;
        
        db.removeTableAtIdx(idx);

        std::cout << "After removing: Number of tables in database: " << std::to_string(db.tables.size()) << std::endl;
    }

    void check_removeTable(Database &db, std::string tableName)
    {

        std::cout << "------------------" << std::endl;
        std::cout << "Before removing: Number of tables in database: " << std::to_string(db.tables.size()) << std::endl;
        std::cout << "Remove table name: " << tableName << std::endl;
        
        db.removeTable(tableName);

        std::cout << "After removing: Number of tables in database: " << std::to_string(db.tables.size()) << std::endl;
    }

    void database_test()
    {

        std::cout << "[===============================================================]" << std::endl;
        std::cout << "[---------------------- Run database test ----------------------]" << std::endl;

        // construct table 1
        std::vector<std::string> schema_item_name_1 = {"s_string", "s_int", "s_float"};
        std::vector<std::string> schema_item_type_1 = {"string", "int", "float"};
        std::vector<SchemaItem> schema_test_1 = prepare_schema(schema_item_name_1, schema_item_type_1);

        std::vector<Row> rows_1;

        std::vector<std::string> new_value_1 = {"string_1", "1", "1.0"};
        std::vector<std::string> new_value_2 = {"string_2", "2", "2.0"};
        std::vector<std::string> new_value_3 = {"string_3", "3", "3.0"};

        rows_1 = prepare_rows(rows_1, new_value_1);
        rows_1 = prepare_rows(rows_1, new_value_2);
        rows_1 = prepare_rows(rows_1, new_value_3);

        Table table_1 = Table("table_1", schema_test_1);
        table_1.rows = rows_1;
        
        // construct table 2
        std::vector<std::string> schema_item_name_2 = {"s_int", "s_float", "s_string"};
        std::vector<std::string> schema_item_type_2 = {"int", "float", "string"};
        std::vector<SchemaItem> schema_test_2 = prepare_schema(schema_item_name_2, schema_item_type_2);

        std::vector<Row> rows_2;

        std::vector<std::string> new_value_4 = {"4", "4.0", "string_4"};
        std::vector<std::string> new_value_5 = {"5", "5.0", "string_5"};
        std::vector<std::string> new_value_6 = {"6", "6.0", "string_6"};

        rows_2 = prepare_rows(rows_2, new_value_4);
        rows_2 = prepare_rows(rows_2, new_value_5);
        rows_2 = prepare_rows(rows_2, new_value_6);

        Table table_2 = Table("table_2", schema_test_2);
        table_2.rows = rows_2;

        // Testing database
        CommandInterpreter ci;
        Database db = Database(&ci);

        std::cout << "====================" << std::endl;
        std::cout << "Check Database::addTable; Database::getTable" << std::endl;
        check_addTable(db, table_1, true);
        check_addTable(db, table_2, true);
        
        std::cout << "====================" << std::endl;
        std::cout << "Check Database::removeTableAtIdx" << std::endl;
        check_removeTableAtIdx(db, 1);
        check_removeTableAtIdx(db, 0);

        std::cout << "====================" << std::endl;
        std::cout << "Check Database::removeTable" << std::endl;
        check_addTable(db, table_1, false);
        check_addTable(db, table_2, false);

        check_removeTable(db, "table_1");
        check_removeTable(db, "table_2");
        
        PASSED;
    }

}