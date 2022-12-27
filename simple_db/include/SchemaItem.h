
#pragma once

#include <string>

// maybe need to support more. 

enum DataType {
    DB_INT,
    DB_FLOAT,
    DB_STRING
};

// A column in a table
class SchemaItem {
    public:
        std::string getName();
        std::string getType();  // convert the enum to string
        std::string name;
        DataType type;
        std::string length_restriction; // well maybe we don't need this

        static DataType getTypeFromString(std::string type);
};
