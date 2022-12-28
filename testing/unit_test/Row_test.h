#pragma once

// test Row class

#include <iostream>
#include <vector>
#include <string>
#include "Row.h"
#include "test.h"

namespace row_test
{
    std::vector<std::string> row_value = {"this", "is", "a", "test", "for", "row"};
    Row row = Row(row_value);

    void check_size(Row row, std::vector<std::string> value)
    {
        auto row_size = row.getValues().size();
        auto value_size = value.size();

        std::cout << " The row size is " << row_size << std::endl;
        std::cout << " The test value size is " << value_size << std::endl;

        EXPECT_EQ(row_size, value_size);
    }

    void check_value(Row row, std::vector<std::string> actual_value)
    {
        auto row_value = row.getValues();

        COUT(row_value, "row_value");
        COUT(actual_value, "actual_value");

        EXPECT_CON_EQ(row_value, actual_value);

    }

    void check_setValue(Row row)
    {
        std::vector<std::string> new_value = {"this", "is", "a", "test"};
        row.setValues(new_value);
        std::vector<std::string> after_set_row_value = row.getValues();
        
        COUT(new_value, "new_value");
        COUT(after_set_row_value, "row value after set");

        EXPECT_CON_EQ(new_value, after_set_row_value);

    }

    void row_test()
    {

        std::cout << "[===============================================================]" << std::endl;
        std::cout << "[------------------------ Run row test -------------------------]" << std::endl;

        std::cout << "====================" << std::endl;
        std::cout << "Check row size" << std::endl;
        check_size(row, row_value);

        std::cout << "====================" << std::endl;
        std::cout << "Check row values" << std::endl;
        check_value(row, row_value);

        std::cout << "====================" << std::endl;
        std::cout << "Check Row::setValues" << std::endl;
        check_setValue(row);

        PASSED;
    }

}