
#pragma once

#include <string>
#include <vector>

// A row in a table
class Row {
    private:
        std::vector<std::string> values;
    public:
        Row();
        Row(std::vector<std::string> values);
        std::vector<std::string> getValues();
        void setValues(std::vector<std::string> values);
};
