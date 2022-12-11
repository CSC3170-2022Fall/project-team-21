
#include <string>
#include "SchemaItem.h"

#include <algorithm>

std::string SchemaItem::getName(){
     return this->name;
}


std::string SchemaItem::getType(){
     // convert the enum to string
     switch (this->type) {
         case INT:
             return "INT";
         case FLOAT:
             return "FLOAT";
         case STRING:
             return "STRING";
         default:
             return "UNKNOWN";
     }
}

DataType SchemaItem::getTypeFromString(std::string type){
     // convert type to uppercase
        std::transform(type.begin(), type.end(), type.begin(), ::toupper);
     if(type == "INT" || type == "INTEGER"){
         return INT;
     }
     if(type == "FLOAT"){
         return FLOAT;
     }
     if(type == "STRING" || type == "VARCHAR" || type == "CHAR"){
         return STRING;
     }
     printf("unknown type: %s\n", type.c_str());
    return STRING;
}
