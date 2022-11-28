
#pragma once

#include <string>

// A column in a table
class Col {
    public:
        Col(std::string name, std::string type, std::string value);
        std::string getName();
        std::string getType();
        std::string getValue();
        void setValue(std::string value);
    private:
        std::string name;
        std::string type;
        std::string value;
};
