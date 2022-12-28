#pragma once

// test Table class

#include <iostream>
#include <vector>
#include <string>
#include "Table.h"
#include "SchemaItem.h"
#include "Row.h"
#include "test.h"

namespace table_test
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

    void check_getRowAt(Table table)
    {
        int row_size = table.getSize();

        for (int i = 0; i < row_size; ++i)
        {
            std::vector<std::string> row_value = table.getRowAt(i).getValues();
            COUT(row_value, ("row "+std::to_string(i)));
        }
    }

    void check_removeRowAt(Table table)
    {

        int row_size = table.getSize();

        for (int i = row_size - 1; i >= 0; --i)
        {
            std::cout << "-------------" << std::endl;
            std::cout << ("remove row at " + std::to_string(i)) << std::endl;
            table.removeRowAt(i);
            table.printOut();
        }
    }

    void check_insertLast(Table table, Row row_insert)
    {
        table.insertLast(row_insert);
        table.printOut();
    }

    void check_insertAt(Table table, Row row_insert, int idx)
    {
        table.insertAt(row_insert, idx);
        table.printOut();
    }

    void check_getSchema(Table table)
    {
        std::cout << table.getSchema() << std::endl;
    }

    void table_test()
    {

        std::cout << "[===============================================================]" << std::endl;
        std::cout << "[----------------------- Run table test ------------------------]" << std::endl;

        std::vector<std::string> schema_item_name = {"s_string", "s_int", "s_float"};
        std::vector<std::string> schema_item_type = {"string", "int", "float"};
        std::vector<SchemaItem> schema_test = prepare_schema(schema_item_name, schema_item_type);

        std::vector<Row> rows;

        std::vector<std::string> new_value_1 = {"string_1", "1", "1.0"};
        std::vector<std::string> new_value_2 = {"string_2", "2", "2.0"};
        std::vector<std::string> new_value_3 = {"string_3", "3", "3.0"};

        rows = prepare_rows(rows, new_value_1);
        rows = prepare_rows(rows, new_value_2);
        rows = prepare_rows(rows, new_value_3);

        Table table = Table("test", schema_test);
        table.rows = rows;

        std::cout << "====================" << std::endl;
        std::cout << "Check Table::printOut" << std::endl;
        table.printOut();

        std::cout << "====================" << std::endl;
        std::cout << "Check Table::getRowAt" << std::endl;
        check_getRowAt(table);

        std::cout << "====================" << std::endl;
        std::cout << "Check Table::removeRowAt" << std::endl;
        check_removeRowAt(table);

        std::cout << "====================" << std::endl;
        std::cout << "Check Table::insertLast" << std::endl;

        std::vector<std::string> new_value_insertLast = {"insertLast", "4", "4.0"};
        check_insertLast(table, new_value_insertLast);
        
        std::cout << "====================" << std::endl;
        std::cout << "Check Table::insertAt" << std::endl;
        std::vector<std::string> new_value_insertAt = {"insertAt", "5", "5.0"};
        check_insertAt(table, new_value_insertAt, 2);

        std::cout << "====================" << std::endl;
        std::cout << "Check Table::getSchema" << std::endl;
        check_getSchema(table);


        PASSED;
    }

}