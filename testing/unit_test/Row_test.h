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

        std::cout << "The row size is " << row_size << std::endl;
        std::cout << "The test value size is " << value_size << std::endl;

        EXPECT_EQ(row_size, value_size);
    }

    void check_value()
    {
        

    }

    void check_setValue()
    {
    }

    void row_test()
    {

        std::cout << "[===============================================================]" << std::endl;
        std::cout << "[----------------- Run container test : deque ------------------]" << std::endl;

        check_size(row, row_value);
        PASSED;
    }

}