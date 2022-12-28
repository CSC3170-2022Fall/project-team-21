
#pragma once

#include <string>

// maybe need to support more.

enum DataType
{
    DB_INT,
    DB_FLOAT,
    DB_STRING
};

// A column in a table
class SchemaItem
{
public:

    SchemaItem();
    SchemaItem(std::string name, DataType type);

    std::string getName();
    std::string getType(); // convert the enum to string
    static DataType getTypeFromString(std::string type);

    std::string name;
    DataType type;
    std::string length_restriction; // well maybe we don't need this
};
