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

    void row_test() {
        Row row = Row(row_value);
    }


}