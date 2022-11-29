
#pragma once

#include <string>

enum DataType {
    INT,
    FLOAT,
    STRING
};

// A column in a table
class SchemaItem {
    public:
        std::string getName();
        std::string getType();
        std::string getValue();
        std::string name;
        DataType type;
        std::string length_restriction;
};
