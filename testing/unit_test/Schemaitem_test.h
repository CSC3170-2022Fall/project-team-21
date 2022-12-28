#pragma once

// test SchemaItem class

#include <iostream>
#include <vector>
#include <string>
#include "SchemaItem.h"
#include "Row.h"
#include "test.h"

namespace schemaitem_test
{

    std::vector<std::string> schema_item_name = {"s_string", "s_int", "s_float"};
    std::vector<std::string> schema_item_type = {"string", "int", "float"};

    void check_getTypeFromString(std::vector<std::string> schema_item_type, std::vector<SchemaItem> schema)
    {
        for (int i = 0; i < schema_item_type.size(); ++i)
        {
            std::cout << "the item type is: " << schema_item_type[i] << 
                "; the corresponding DataType is " << SchemaItem::getTypeFromString(schema_item_type[i]) << 
                "; DataType from getType is: " << schema[i].getType() << std::endl;
        }
    }

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

    void schemaitem_test()
    {

        std::cout << "[===============================================================]" << std::endl;
        std::cout << "[--------------------- Run schemaitem test ---------------------]" << std::endl;

        std::cout << "====================" << std::endl;
        std::vector<SchemaItem> schema_test = prepare_testcase(schema_item_name, schema_item_type);
        check_getTypeFromString(schema_item_type, schema_test);

        PASSED;
    }

}