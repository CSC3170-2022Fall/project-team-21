#pragma once
#include <string>
#include "Table.h"


// we might need a quick evaluator for conditions, 
// which appears in the `where` clause of a query
class Conditions
{
private:
    std::string condition;
public:
    Conditions(/* args */);

    bool conditionMatched(Table table, std::string condition);
};

