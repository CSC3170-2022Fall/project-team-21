
#include <string>
#include "Row.h"

// Please modify to make build work
Row::Row(){}
Row::Row(std::vector<std::string> values){
      this->values = values;
}

std::vector<std::string> Row::getValues(){
      return this->values;
}

void Row::setValues(std::vector<std::string> values){
      this->values = values;
}

