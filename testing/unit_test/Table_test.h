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

    void check_getRowAt(Row row)
    {
    }

    void check_removeRowAt(Row row)
    {
    }

    void check_insertLast(Row row)
    {
    }

    void check_insertAt(Row row)
    {
    }

    void check_getSchema(Row row)
    {
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


        // std::cout << "Check row size" << std::endl;
        // // check_size(row, row_value);

        // std::cout << "====================" << std::endl;
        // std::cout << "Check row values" << std::endl;
        // // check_value(row, row_value);

        // std::cout << "====================" << std::endl;
        // std::cout << "Check Row::setValues" << std::endl;
        // // check_setValue(row);

        // PASSED;
    }

}