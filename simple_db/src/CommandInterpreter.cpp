#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "CommandInterpreter.h"
#include <algorithm>

#ifndef INT_MIN
#define INT_MIN -2147483648
#endif

using namespace std;

CommandInterpreter::CommandInterpreter()
{
}

void CommandInterpreter::execute(std::string command, Database *db)
{
      // split the command into tokens by whitespace
      // like in python, string.split(" ")
      // please make it work for any number of whitespace
      // for better processing
      std::vector<std::string> v_command = tokenizer(command);

      if (v_command[0] == "select")
      {
            // first find the index of "from"
            int idx_of_from;
            // parse(command[idx_of_from:])  // TODO
      }
      else if (v_command[0] == "create" && v_command[1] == "table")
      {
            // call the create table handler
            createTable(&v_command);
      }
      else if (v_command[0] == "exit" || v_command[0] == "q" || v_command[0] == "quit")
      {
            // first save to file, then return
            exitCommand();
      }
      else if (v_command[0] == "insert" && v_command[1] == "into")
      {
            // call the insert handler
            insertCommand(&v_command);
      }
      else if (v_command[0] == "load")
      {
            this->load(v_command);
      }
      else if (v_command[0] == "print")
      {
            printTable(&v_command);
      }
      else if (v_command[0] == "help" || v_command[0] == "h")
      {
            printf("    Help message here. List of all SQL commands we support:\n");
            printf("    create table <table name> (<column name>);\n");
            printf("    create table <table name> as <select clause>;\n");
            printf("    load <table name>;\n");
            printf("    store <table name>;\n");
            printf("    insert into <table name> values <literal>;\n");
            printf("    print <table name>;'\n");
            printf("    quit;\n");
            printf("    exit;\n");
            printf("    select <column name> from <table name> <conditional clause>;\n");
            printf("    select <column name> from <table name1>,<table name2> <conditional clause>;\n");
      }
      else if (v_command[0] == "/*") // do nothing if user input a comment
      {
            printf("");
      }
      else
      {
            printf("Invalid command, please try again.\n");
            Spelling_error_correction(&v_command);
            // guessUserInput(v_command); // guess the input of the user
            // 也可以使用Spelling_error_correction实现拼写错误的改正与纠错。
      }
}

void CommandInterpreter::insertCommand(std::vector<std::string> *v_command)
{
      // insert to <table_name> values <value1>, <value2>, ...
      string tableName = v_command->at(2);
      // if tablename contains brackets, ignore them
      if (tableName[tableName.length() - 1] == ')')
      {
            tableName = tableName.substr(0, tableName.find_first_of('('));
      }
      Table *target_table = this->database->getTable(tableName);

      vector<string> values;
      for (int i = 4; i < v_command->size(); i++)
      {
            values.push_back(v_command->at(i));
      }
      Row newRow = Row(values);
      target_table->insertLast(newRow);
}

// should use each function for one type of command
// please add the parameters as you want, maybe the Database object pointer
void CommandInterpreter::createTable(std::vector<std::string> *v_command)
{
      string tableName = v_command->at(2);
      vector<SchemaItem> schema;

      int i = 4;
      while (i < v_command->size())
      {
            string schemaItem = v_command->at(i);
            DataType schemaType;
            string schemaName;
            // if schemaItem contains brackets
            if (schemaItem[schemaItem.length() - 1] == ')')
            {
                  schemaName = schemaItem.substr(0, schemaItem.find('('));
                  schemaType = SchemaItem::getTypeFromString(schemaItem.substr(
                      schemaItem.find('(') + 1, schemaItem.find(')') - schemaItem.find('(') - 1));
            }
            else
            {
                  schemaType = SchemaItem::getTypeFromString(
                      v_command->at(++i));
                  schemaName = schemaItem;
            }
            SchemaItem newSchemaItem = SchemaItem();
            newSchemaItem.name = schemaName;
            newSchemaItem.type = schemaType;
            schema.push_back(newSchemaItem);
            i++;
      }
}
void CommandInterpreter::exitCommand()
{
      cout << "Bye!" << endl;
      exit(0);
}

void CommandInterpreter::load(std::vector<std::string> v_command)
{
      string tableName;
      tableName = v_command[1];
      Table tableTemp;
      tableTemp = tableTemp.loadFromFile(tableName, this->database->name);
      this->database->addTable(tableTemp);
      cout << "Loaded " << v_command[1] << ".db" << endl; // 跟ucb那个输出格式一致吧:loaded students.db
}

void CommandInterpreter::printTable(std::vector<std::string> *v_command)
{
      string target_table_name = v_command->at(1);
      Table *target_table = this->database->getTable(target_table_name);
      if (target_table != NULL){
            target_table->printOut();
      }
      else{       //we cannot find the table we want to print in the database
            cout << "Error: Cannot find the table: " << target_table_name << endl;
      }
}

Table CommandInterpreter::select()
{
      // fill in
      printf("Search results:\n");
}

/* 
guess the input of the user,
for example, if user make a typo: "crate table",
the databse system will ask the user whether he/she means "create table"
*/
void CommandInterpreter::guessUserInput(std::vector<std::string> v_command)
{
      string input;
      input = v_command[0].substr(0, 2);
      if (input == "cr")
      {
            printf("Do you mean command 'create table'?\n");
      }
      else if (input == "lo")
      {
            printf("Do you mean command 'load'?\n");
      }
      else if (input == "st")
      {
            printf("Do you mean command 'store'?\n");
      }
      else if (input == "in")
      {
            printf("Do you mean command 'insert into'?\n");
      }
      else if (input == "pr")
      {
            printf("Do you mean command 'print'?\n");
      }
      else if (input == "qu")
      {
            printf("Do you mean command 'quit'?\n");
      }
      else if (input == "ex")
      {
            printf("Do you mean command 'exit'?\n");
      }
      else if (input == "se")
      {
            printf("Do you mean command 'select'?\n");
      }
      else if (input == "//")
      {
            printf("Do you want to make comments? Please use '/*' to begin with your commands.\n");
      }
      printf("Type in 'help' or 'h' for more help.\n");
}

// Segment string into tokens, split by " "
std::vector<std::string> CommandInterpreter::tokenizer(std::string str)
{
      std::stringstream ss(str);
      std::vector<std::string> tokens;
      std::string word;
      while (ss >> word)
      {
            // convert word to lowercase
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            tokens.push_back(word);
      }
      ss.clear();
      tokens[tokens.size()-1] = tokens[tokens.size()-1].substr(0, tokens[tokens.size()-1].length()-1);
      return (tokens);
}

void CommandInterpreter::Spelling_error_correction(std::vector<std::string> *v_command)
{
      // 这个函数用来与lcs函数共同完成对于拼写错误的改正与纠错，注意，它只能纠错第一个单词！具体方法见lcs函数注释。
      std::string a = v_command->at(0);
      std::string b = "select";
      std::string c = "create";
      std::string d = "exit";
      std::string e = "insert";
      std::string f = "load";
      std::string g = "print";
      std::string h = "help";
      // 有新的操作时就再往后加
      std::string i = "select";
      std::string j = "select";

      int a1 = lcs(a, b);
      int a2 = lcs(a, c);
      int a3 = lcs(a, d);
      int a4 = lcs(a, e);
      int a5 = lcs(a, f);
      int a6 = lcs(a, g);
      int a7 = lcs(a, h);

      if (a1 >= 4)
      {
            cout << "You might be trying to select";
            // first find the index of "from"
            int idx_of_from;
            // parse(command[idx_of_from:])  // TODO
      }
      else if (a2 >= 3)
      {
            cout << "You might be trying to creat" << endl;
            // createTable(&v_command);
      }
      else if (a3 >= 3)
      {
            cout << "You might be trying to exit" << endl;
            // exitCommand();
      }
      else if (a4 >= 4)
      {
            cout << "You might be trying to insert" << endl;
            // insertCommand(&v_command);
      }
      else if (a5 >= 3)
      {
            cout << "You might be trying to load" << endl;
            // this->load(v_command);
      }
      else if (a6 >= 3)
      {
            cout << "You might be trying to print" << endl;
            // printTable(&v_command);
      }
      else if (a7 >= 3)
      {
            cout << "You might be trying to help" << endl;
            // printf("Help message here\n");
      }
      else
      {
            printf("Invalid command, please try again.\n");
      }
}

int CommandInterpreter::lcs(string a, string b)
{
      // 计算a，b最长公共子字符串长度。
      // 这个函数经过测试没有问题
      int n = a.length();
      int m = b.length();
      int long_sub = INT_MIN;

      // 新建堆区数据
      int **arr = new int *[n];
      for (int i = 0; i < n; ++i)
            arr[i] = new int[m];

      // 初始化第一列
      for (int i = 0; i < n; ++i)
      {
            if (a[i] == b[0])
                  arr[i][0] = 1;
            else
            {
                  if (i != 0)
                        arr[i][0] = arr[i - 1][0];
                  else
                        arr[i][0] = 0;
            }
      }

      // 初始化第一列
      for (int j = 0; j < m; ++j)
      {
            if (a[0] == b[j])
                  arr[0][j] = 1;
            else
            {
                  if (j != 0)
                        arr[0][j] = arr[0][j - 1];
                  else
                        arr[0][j] = 0;
            }
      }

      for (int i = 1; i < n; ++i)
      {
            for (int j = 1; j < m; ++j)
            {
                  if (a[i] == b[i])
                        arr[i][j] = max(max(arr[i][j - 1], arr[i - 1][j]), arr[i - 1][j - 1] + 1);
                  else
                        arr[i][j] = max(max(arr[i][j - 1], arr[i - 1][j]), arr[i - 1][j - 1]);
            }
      }

      return arr[n - 1][m - 1]; // 返回最长公共子字符串长度.
}
