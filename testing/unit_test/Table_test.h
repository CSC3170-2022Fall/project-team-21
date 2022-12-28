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

    std::vector<std::string> schema_item_name = {"s_string", "s_int", "s_float"};
    std::vector<std::string> schema_item_type = {"string", "int", "float"};

    // prepare for the test case
    std::vector<SchemaItem> prepare_testcase(std::vector<std::string> name, std::vector<std::string> type)
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

    void check_table(Row row, std::vector<std::string> value)
    {
        auto row_size = row.getValues().size();
        auto value_size = value.size();

        std::cout << " The row size is " << row_size << std::endl;
        std::cout << " The test value size is " << value_size << std::endl;

        EXPECT_EQ(row_size, value_size);
    }

    void check_getRowAt(Row row)
    {
    }

    // void check_getRowAt(Row row)
    // {
    // }

    // void check_getRowAt(Row row)
    // {
    // }

    void table_test()
    {

        std::cout << "[===============================================================]" << std::endl;
        std::cout << "[----------------------- Run table test ------------------------]" << std::endl;
        std::vector<SchemaItem> test = prepare_testcase(schema_item_name, schema_item_type);

        // std::cout << "====================" << std::endl;
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