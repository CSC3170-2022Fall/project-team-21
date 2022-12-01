
#pragma once

#include <string>

// maybe need to support more. 

enum DataType {
    INT,
    FLOAT,
    STRING
};

// A column in a table
class SchemaItem {
    public:
        std::string getName();
        std::string getType();  // convert the enum to string
        std::string name;
        DataType type;
        std::string length_restriction; // well maybe we don't need this
};
