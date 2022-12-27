
#include <string>
#include "SchemaItem.h"

#include <algorithm>

SchemaItem::SchemaItem() {}

SchemaItem::SchemaItem(std::string name, DataType type)
{
    this->name = name;
    this->type = type;
}

std::string SchemaItem::getName()
{
    return this->name;
}

std::string SchemaItem::getType()
{
    // convert the enum to string
    switch (this->type)
    {
    case DB_INT:
        return "INT";
    case DB_FLOAT:
        return "FLOAT";
    case DB_STRING:
        return "STRING";
    default:
        return "UNKNOWN";
    }
}

DataType SchemaItem::getTypeFromString(std::string type)
{
    // convert type to uppercase
    std::transform(type.begin(), type.end(), type.begin(), ::toupper);
    if (type == "INT" || type == "INTEGER" || type == "(INT)" || type == "(INTEGER)")
    {
        return DB_INT;
    }
    if (type == "FLOAT" || type == "DOUBLE" || type == "(FLOAT)" || type == "(DOUBLE)" || type == "NUMERIC" || type == "(NUMERIC)")
    {
        return DB_FLOAT;
    }
    if (type == "STRING" || type == "VARCHAR" || type == "(STRING)" || type.find("CHAR") != std::string::npos)
    {
        return DB_STRING;
    }
    printf("unknown type: %s\n", type.c_str());
    return DB_STRING;
}
