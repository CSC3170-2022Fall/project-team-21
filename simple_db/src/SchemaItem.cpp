
#include <string>
#include "SchemaItem.h"



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
     if(type == "INT"){
         return INT;
     }
     if(type == "FLOAT"){
         return FLOAT;
     }
     if(type == "STRING"){
         return STRING;
     }
     return STRING;
}
