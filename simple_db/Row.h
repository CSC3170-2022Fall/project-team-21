
#pragma once

#include <string>

// A row in a table
class Row {
    private:
        std::string name;
        std::string type;
        std::string value;
    public:
        Row(std::string name, std::string type, std::string value);
        std::string getName();
        std::string getType();
        std::string getValue();
        void setValue(std::string value);
};
