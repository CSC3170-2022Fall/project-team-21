#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "CommandInterpreter.h"
#include <algorithm>
#include <map>

#ifndef INT_MIN
#define INT_MIN -2147483648
#endif

using namespace std;

CommandInterpreter::CommandInterpreter()
{
}

bool CommandInterpreter::getInputCommand(vector<std::string> &v_command, bool command_continue)
{

	printf("> ");
	string command;
	bool get_command = false;
	getline(cin, command);

	// allow these simple commands to not have a semicolon
	if (command == "quit" || command == "exit" || command == "h" || command == "help" || command == "q")
	{
		v_command.push_back(command);
		get_command = true;
	}
	else
	{

		if (command.length() == 0 || (command[command.length() - 1] == '/' && command[command.length() - 2] == '*'))
		{
			get_command = true;
		}
		else
		{
			while (true)
			{
				if (command.find(';') != string::npos)
				{

					if (!command_continue)
					{ // complete command
						command = command.substr(0, command.find(';'));
						v_command = tokenizer(command);

						// if (v_command)
					}
					else
					{ // incomplete command: the last line
						vector<std::string> tmp_v_command;
						command = command.substr(0, command.find(';'));
						tmp_v_command = tokenizer(command);
						v_command.insert(v_command.end(), tmp_v_command.begin(), tmp_v_command.end());
					}
					get_command = true;
					break;
				}

				// no ; found: part of the command, support multiline input
				command_continue = true;
				vector<std::string> tmp_v_command;
				tmp_v_command = tokenizer(command);
				v_command.insert(v_command.end(), tmp_v_command.begin(), tmp_v_command.end());
                        // printf("The input must end with a semicolon(;). Please input again.\n");
				printf("> ");
				getline(cin, command);
			}
		}
	}

	return get_command;
}

// Segment string into tokens, split by " "
std::vector<std::string> CommandInterpreter::tokenizer(std::string str)
{
	std::stringstream ss(str);
	std::vector<std::string> tokens;
	std::string word;
	while (ss >> word)
	{
		if (word != " ")
			tokens.push_back(word);
	}
	ss.clear();
	// we've removed the ; in main.cpp, so we don't need to remove it here
	// tokens[tokens.size()-1] = tokens[tokens.size()-1].substr(0, tokens[tokens.size()-1].length()-1);
	return (tokens);
}

int CommandInterpreter::findTable(string tableName)
{
	Table *target_table = this->database->getTable(tableName);
	if (target_table == NULL)
	{ // 找不到这个table
		//printf("Error: The name of the table you want to search does not exist in this database.\n", tableName.c_str());
		return 0;
	}
	else
	{
		return 1;
	}
}

//只能判别最后一个select子查询
int CommandInterpreter::judgeSelect(std::vector<std::string> v_command){
      //判断table是否存在
      int cri = 1;   //有没错误
	  int selectIndex;  //select
      
	  string temp;
	  vector<int> selectFrom;
	  int leftParenthesis = 0;   //左括号的数量
	  int rightParenthesis = 0;  //右括号的数量
	  for (int i = 0; i < v_command.size(); i++)
      {
		    temp = v_command[i];
			for (int j = 0; j < temp.length(); j++){
				temp[j] = tolower(temp[j]);
				if (temp[j] == '('){    
					leftParenthesis += 1;
				}
				if (temp[j] == ')'){
					rightParenthesis += 1;
				}
			}
			if (temp.find("select") != string::npos) //考虑到可能有“（select”这种情况出现
            // if (v_command[i].find("select") != string::npos) //考虑到可能有“（select”这种情况出现
            {
				  selectFrom.push_back(i);
                  //break;
            }
			if (temp.find("from") != string::npos) //考虑到可能有“（select”这种情况出现
            // if (v_command[i].find("select") != string::npos) //考虑到可能有“（select”这种情况出现
            {
				  selectFrom.push_back(i);
                  //break;
            }

      }
	 
	//左/右括号的数量应该等于select的数量 - 1
	  if ( (leftParenthesis != rightParenthesis) || ( leftParenthesis != (selectFrom.size()/2 - 1) ) || ( rightParenthesis != (selectFrom.size()/2 - 1) )  ){
			printf("Error: Please write the correct number of left-parentheses('(') and right-parentheses(')') in your input command.\n");
			cri = 0;
			return cri;
	  }
	  //cout << fromIndex << " ";
	  int fromIndex = selectFrom[selectFrom.size() - 1];   //最后一个from
	  int parenthesisIndex = -1;
	  for (int i = (fromIndex + 1); i < v_command.size(); i++)
      {
            if(v_command[i].find(")") != string::npos){
				  parenthesisIndex = i;
                  break;
            }
      }

	  if (parenthesisIndex == -1)   //当然，并不是每个select命令都有括号（即不是嵌套select时）
	  {
			parenthesisIndex = v_command.size() - 1;
	  }

      int whereIndex = -1; //where
      //for (int i = v_command.size() - 1; i >= 0; i--)
	  for (int i = (fromIndex + 1); i < parenthesisIndex; i++)
      {
			temp = v_command[i];
			for (int j = 0; j < temp.length(); j++){
				temp[j] = tolower(temp[j]);
			}
            // if (v_command[i].find("where") != string::npos)
			if (temp.find("where") != string::npos)
            {
				  //cout << temp << " ";
                  whereIndex = i;	 //找与最后一个select在同一个括号内的where的位置索引
                  break;
            }
      }

      int tableNum;
      if (whereIndex == -1){  //select语句中没有where
            // tableNum = parenthesisIndex - fromIndex - 1;
			tableNum = parenthesisIndex - fromIndex;
      }
      else{
            tableNum = whereIndex - fromIndex - 1; 
      }
      string tableName;
      // int find;
      vector<SchemaItem> allSchema;

      for (int i = 0; i < tableNum; i++){
            tableName = v_command[fromIndex + i + 1];
            if (tableName.find(',') != string::npos)
            // if (   tableName[tableName.length() - 1] == ',' )
            {
                  tableName = tableName.substr(0, tableName.length() - 1);
            }
			while (tableName.find(')') != string::npos)  //没有where跟在后面的话，可能会嵌套很多个）括号,所以要删掉好几个）号
            // if (   tableName[tableName.length() - 1] == ',' )
            {
                  tableName = tableName.substr(0, tableName.length() - 1);
            }
            Table *target_table = this->database->getTable(tableName);
            if (target_table == NULL){  //找不到这个表
                  cout << "Error: cannot find the table " << tableName << " in the database." << endl;
                  cri = 0;
                  return cri;
            }
            else{
                  allSchema.insert(allSchema.end(), (target_table->schema).begin(), (target_table->schema).end());
            }
      }
	
      //判断列名是否存在
      string columnName;
      bool find;

	  //select 列名 from
	  for (int k = 0; k < selectFrom.size()/2; k++)
	  {
			selectIndex = selectFrom[k * 2];
			fromIndex = selectFrom[k * 2 + 1];
			if (v_command[selectIndex + 1] != "*"){
				//逐个逐个列名找
				for (int i = (selectIndex + 1); i < fromIndex; i++){
					find = false;
					columnName = v_command[i];
					// cout << columnName << endl;
					if (   columnName[columnName.length() - 1] == ',' )
					{
							columnName = columnName.substr(0, columnName.length() - 1);
					}
					for (int j = 0; j < allSchema.size(); j++){
							if (columnName == allSchema[j].name){
								find = true;
								break;
							}
					}
					if (find == false){
							cri = 0;
							cout << "Error: cannot find the column name " << columnName << " in the table you want to search." << endl;
							return cri;
					}
					
				}
			}
	  }

      return cri;

}

void CommandInterpreter::execute(vector<std::string> v_command, Database *db)
{
	this->database = db;

	if (v_command.size() == 0)
	{
		return;
	}

	// convert the first token to lowercase
	std::transform(v_command[0].begin(), v_command[0].end(), v_command[0].begin(), ::tolower);

	if (v_command[0] == "select")
	{
		
		int cri = judgeSelect(v_command);   //validity check for whether the table and column exists
		if (cri == 1){
			printf("Search results:\n");
			Table tb = select(v_command);
			tb.printOut();
		}
	}
	else if (v_command[0] == "create")
	{
		// convert the second token to lowercase
		std::transform(v_command[1].begin(), v_command[1].end(), v_command[1].begin(), ::tolower);
		if (v_command[1] == "table")
		{
			// call the create table handler
			createTable(&v_command);
		}
		else
		{
			spellingErrorCorrection(&v_command);
		}
	}
	else if (v_command[0] == "delete")
	{
		std::transform(v_command[1].begin(), v_command[1].end(), v_command[1].begin(), ::tolower);
		if (v_command[1] == "table")
		{
			deleteTable(&v_command);
		}
            else if (v_command[1] == "from")
		{
			deleteRow(v_command);
		}
		else
		{
			spellingErrorCorrection(&v_command);
		}
	}
	else if (v_command[0] == "insert")
	{
		// convert the second token to lowercase
		std::transform(v_command[1].begin(), v_command[1].end(), v_command[1].begin(), ::tolower);

		if (v_command[1] == "into")
		{
			// call the insert handler
			insertCommand(&v_command);
		}
		else
		{
			spellingErrorCorrection(&v_command);
		}
	}
	else if (v_command[0] == "load")
	{
		this->load(v_command);
	}
	else if (v_command[0] == "store")
	{
		this->store(&v_command);
	}
	else if (v_command[0] == "print")
	{
		printTable(&v_command);
	}
	else if (v_command[0] == "exit" || v_command[0] == "q" || v_command[0] == "quit")
	{
		// first save to file, then return
		exitCommand();
	}
	else if (v_command[0] == "help" || v_command[0] == "h")
	{
		printf("Help message here. List of all SQL commands we support:\n");
		printf("    create table <table name> (<column name>);\n");
		printf("    create table <table name> as <select clause>;\n");
		printf("    load <table name>;\n");
		printf("    store <table name>;\n");
		printf("    insert into <table name> values <literal>;\n");
		printf("    print <table name>;'\n");
		printf("    quit;\n");
		printf("    exit;\n");
    	printf("    delete from <table name> (<conditional clause>)\n");
		printf("    select <column name> from <table name> <conditional clause>;\n");
		printf("    select <column name> from <table name1>,<table name2> <conditional clause>;\n");
	}
	else if (v_command[0] == "/*") // do nothing if user input a comment
	{
	}
	else
	{
		spellingErrorCorrection(&v_command);
	}
}

void CommandInterpreter::store(std::vector<std::string> *v_command)
{
	// store <table name>;
	if (v_command->size() > 1)
	{
		string tableName = v_command->at(1);
		Table *tb = this->database->getTable(tableName);
		if (tb == NULL)
		{
			printf("Error: Table %s does not exist.\n", tableName.c_str());
			return;
		}
		tb->saveToFile(tb->name);
            printf("Store process completed.\n");
	}
	else
	{
		cout << "Error: Please give the name of the table" << endl;
	}
}

void CommandInterpreter::insertCommand(std::vector<std::string> *v_command)
{
	/*
	INSERT INTO Customers (CustomerName, ContactName, Address, City, PostalCode, Country)
	VALUES ('Cardinal', 'Tom B. Erichsen', 'Skagen 21', 'Stavanger', '4006', 'Norway');
	*/
	// insert to <table_name> values <value1>, <value2>, ...
	string tableName = v_command->at(2);

	// strip the comma
	for (int i = 0; i < v_command->size(); i++)
	{
		if (v_command->at(i)[v_command->at(i).length() - 1] == ',')
		{
			v_command->at(i) = v_command->at(i).substr(0, v_command->at(i).length() - 1);
		}
	}

	// strip the brackets
	for (int i = 0; i < v_command->size(); i++)
	{
		if (v_command->at(i) == "(")
		{
			v_command->erase(v_command->begin() + i);
		}
		if (v_command->at(i) == ")")
		{
			v_command->erase(v_command->begin() + i);
		}
	}
	for (int i = 0; i < v_command->size(); i++)
	{
		if (v_command->at(i)[0] == '(')
		{
			v_command->at(i) = v_command->at(i).substr(1);
		}
		if (v_command->at(i)[v_command->at(i).length() - 1] == ')')
		{
			v_command->at(i) = v_command->at(i).substr(0, v_command->at(i).length() - 1);
		}
	}

	Table *target_table = this->database->getTable(tableName);
	if (target_table == NULL)
	{
		printf("Error: Table %s does not exist.\n", tableName.c_str());
		return;
	}

	vector<SchemaItem> schema = target_table->schema;
	// // create a mapping between the column name and the index in the schema
	// map<string, int> schema_map;
	// for (int i = 0; i < schema.size(); i++)
	// {
	//       schema_map[schema[i].name] = i;
	// }

	vector<string> values;

	// get the pos of "values" or "VALUES"...(regardless of arbitrary upper cases or lower cases)
	int pos = 0;
	string temp;
	for (int i = 0; i < v_command->size(); i++)
	{
		temp = v_command->at(i);
		for (int j = 0; j < temp.length(); j++){
			temp[j] = tolower(temp[j]);
		}
		// if (v_command->at(i) == "values" || v_command->at(i) == "VALUES")
		if (temp == "values")
		{
			pos = i;
			break;
		}
	}

	// record the mapping in the sql command, if there is any
	// map the value idx to the schema name
	// map<int, string> tmpmap;
	// if (pos != 3)
	// {
	//       for (int i = 3; i < pos; i++)
	//       {
	//             values[schema_map[v_command->at(i)]] = v_command->at(i + 1);
	//       }
	// }
	int i = pos + 1;
	while (i < v_command->size())
	{
		// strip the quotation marks, if the quote is not complete, join with the next string
		// support this case: `insert into schedule values '22100', 'Math abcd', '60 Evans';`
		if (v_command->at(i)[0] == '\'' && v_command->at(i)[v_command->at(i).length() - 1] != '\'')
		{
			v_command->at(i) = v_command->at(i).substr(1);
			while (v_command->at(i)[v_command->at(i).length() - 1] != '\'')
			{
				v_command->at(i) = v_command->at(i) + " " + v_command->at(i + 1);
				v_command->erase(v_command->begin() + i + 1);
			}
			v_command->at(i) = v_command->at(i).substr(0, v_command->at(i).length() - 1);
		}
		else if (v_command->at(i)[0] == '\'' && v_command->at(i)[v_command->at(i).length() - 1] == '\'')
		{
			v_command->at(i) = v_command->at(i).substr(1, v_command->at(i).length() - 2);
		}

		// repeat for the double quote
		if (v_command->at(i)[0] == '\"' && v_command->at(i)[v_command->at(i).length() - 1] != '\"')
		{
			v_command->at(i) = v_command->at(i).substr(1);
			while (v_command->at(i)[v_command->at(i).length() - 1] != '\"')
			{
				v_command->at(i) = v_command->at(i) + " " + v_command->at(i + 1);
				v_command->erase(v_command->begin() + i + 1);
			}
			v_command->at(i) = v_command->at(i).substr(0, v_command->at(i).length() - 1);
		}
		else if (v_command->at(i)[0] == '\"' && v_command->at(i)[v_command->at(i).length() - 1] == '\"')
		{
			v_command->at(i) = v_command->at(i).substr(1, v_command->at(i).length() - 2);
		}

		values.push_back(v_command->at(i));
		i++;
	}
	Row newRow = Row(values);
	if (newRow.values.size() != schema.size())
	{
		printf("Error: The number of values does not match the number of columns.\n");
		return;
	}
	target_table->insertLast(newRow);
    printf("Insert process completed.\n");
}

void CommandInterpreter::deleteTable(std::vector<std::string> *v_command)
{

	// sample: delete table students;
	string tableName = v_command->at(2);
	int idx = -1;

	for (int i = 0; i < this->database->tables.size(); i++)
	{
		if (this->database->tables[i].name == tableName)
		{
			idx = i;
			this->database->tables.erase(this->database->tables.begin() + idx);
                  cout << "Table " << tableName << " has been deleted" << endl;
			return;
		}
	}
	if (idx == -1)
	{ // the table we search is not found
		cout << "Error: The table " << tableName << " does not exist in this database." << endl;
	}
}

// should use each function for one type of command
// please add the parameters as you want, maybe the Database object pointer
void CommandInterpreter::createTable(std::vector<std::string> *v_command)
{
	/*
		  CREATE TABLE Persons (
		  PersonID int,
		  LastName varchar(255),
		  FirstName varchar(255),
		  Address varchar(255),
		  City varchar(255)
		  );
	*/	

	string tableName = v_command->at(2);

	//name already exists
	// Table *target_table = this->database->getTable(tableName);
	// if (target_table != NULL)
	// {
	//     cout << "Error: The name of the table (" << tableName << ") already exists in this database."<< endl;
	// 	return;
	// }

	vector<SchemaItem> schema;

	// strip the comma
	for (int i = 3; i < v_command->size(); i++)
	{
		if (v_command->at(i)[v_command->at(i).length() - 1] == ',')
		{
			v_command->at(i) = v_command->at(i).substr(0, v_command->at(i).length() - 1);
		}
	}

	// strip the brackets
	for (int i = 0; i < v_command->size(); i++)
	{
		if (v_command->at(i) == "(")
		{
			v_command->erase(v_command->begin() + i);
		}
		if (v_command->at(i) == ")")
		{
			v_command->erase(v_command->begin() + i);
		}
	}
	// for (int i = 0; i < v_command->size(); i++)
	// {
	//       if (v_command->at(i)[0] == '(')
	//       {
	//             v_command->at(i) = v_command->at(i).substr(1);
	//       }
	//       if (v_command->at(i)[v_command->at(i).length() - 1] == ')')
	//       {
	//             v_command->at(i) = v_command->at(i).substr(0, v_command->at(i).length() - 1);
	//       }
	// }

	// delete the "as"'
	string temp;
	temp = v_command->at(3);
	for (int i = 0; i < temp.length(); i++){
		temp[i] = tolower(temp[i]);
	}
	// if ((v_command->at(3) == "as") || (v_command->at(3) == "AS"))
	if (temp == "as")
	{
		v_command->erase(v_command->begin() + 3);
	}
	temp = v_command->at(3);
	for (int i = 0; i < temp.length(); i++){
		temp[i] = tolower(temp[i]);
	}
	// if ((v_command->at(3) == "select") || (v_command->at(3) == "SELECT"))
	// if (temp == "select")
	if (temp.find("select") != string::npos)
	{
		// create v_command copy starting from 4
		vector<string> v_command_copy;
		for (int i = 3; i < v_command->size(); i++)
		{
			v_command_copy.push_back(v_command->at(i));
		}
		int cri = judgeSelect(v_command_copy);   //validity check for whether the table and column exists in the select clause
		if (cri == 1){
			Table tb = select(v_command_copy);
			tb.name = tableName;
			this->database->tables.push_back(tb);
			cout << "Table " << tableName << " has been created." << endl;
		}
		return;
	}

	int i = 3;
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
	Table newTable = Table(tableName, schema);
	this->database->addTable(newTable);
    cout << "Table " << tableName << " has been created." << endl;
}
void CommandInterpreter::exitCommand()
{
	cout << "Bye!" << endl;
	exit(0);
}

void CommandInterpreter::load(std::vector<std::string> v_command)
{
	if (v_command.size() > 1)
	{
		string tableName;
		tableName = v_command[1];
		Table tableTemp;
		tableTemp = tableTemp.loadFromFile(tableName, this->database->name);
		this->database->addTable(tableTemp);
	}
	else
	{
		cout << "Error: Please give the name of the table" << endl;
	}
}

void CommandInterpreter::printTable(std::vector<std::string> *v_command)
{
	if (v_command->size() > 1)
	{
		string target_table_name = v_command->at(1);
		Table *target_table = this->database->getTable(target_table_name);

		if (target_table != NULL)
		{
			printf("Contents of %s:\n", target_table->name.c_str());
			target_table->printOut();
		}
		else
		{ // we cannot find the table we want to print in the database
			cout << "Error: Cannot find table " << target_table_name << " in the database." << endl;
		}
	}
	else
	{
		cout << "Error: Please give the name of the table" << endl;
	}
}

Table CommandInterpreter::select(std::vector<std::string> v_command)
{
	// fill in
	Table result;
	vector<Row> rowsRusult;
	vector<SchemaItem> schemaRusult;

	string tmp;
	int fromIndex;
	for (int i = 1; i < v_command.size(); i++)
	{
		tmp = v_command[i];
		for (int j = 0; j < tmp.length(); j++){
			tmp[j] = tolower(tmp[j]);
		}
		if (tmp.find("from") != string::npos)
		// if (v_command[i].find("from") != string::npos)
		{
			fromIndex = i;
			break;
		}
	}
	int whereIndex = -1;
	for (int i = v_command.size() - 1; i >= 0; i--)
	{
		if(v_command[i].find(")") != string::npos){
			break;
		}
		tmp = v_command[i];
		for (int j = 0; j < tmp.length(); j++){
			tmp[j] = tolower(tmp[j]);
		}
		// if (v_command[i].find("where") != string::npos)
		if (tmp.find("where") != string::npos)
		{
			whereIndex = i;
			break;
		}
	}

	Table tableSource;
	if ((whereIndex - fromIndex == 3) || ((v_command.size() - fromIndex == 3) && (whereIndex == -1)))
	{ // natural inner product
		string tableName1 = v_command[fromIndex + 1];
		string tableName2 = v_command[fromIndex + 2];
		if (tableName1.find(',') != string::npos)
		{
			tableName1 = tableName1.substr(0, tableName1.length() - 1);
		}
		tableSource = naturalInnerProduct(tableName1, tableName2);
	}
	else if ((whereIndex - fromIndex == 2) || ((v_command.size() - fromIndex == 2) && (whereIndex == -1)))
	{ // one table
		string tableName1 = v_command[fromIndex + 1];
		if (tableName1.find(',') != string::npos)
		{
			tableName1 = tableName1.substr(0, tableName1.length() - 1);
		}
		tableSource = *(this->database->getTable(tableName1));
	}
	else if ((whereIndex - fromIndex > 3) || ((v_command.size() - fromIndex > 3) && (whereIndex == -1)))
	{ // recursive
		vector<string> input;
		if(whereIndex != -1){
			for (int i = fromIndex + 1; i < whereIndex; i++)
			{
				string temp = v_command[i];
				if (temp.find(')') != string::npos)
				{
					temp = temp.substr(0, temp.length() - 1);
				}
				input.push_back(temp);
			}
		}
		else{
			for (int i = fromIndex + 1; i < v_command.size(); i++)
			{
				string temp = v_command[i];
				if (temp.find(')') != string::npos)
				{
					temp = temp.substr(0, temp.length() - 1);
				}
				input.push_back(temp);
			}
		}
		
		tableSource = select(input);
	}

	vector<int> inputSchemaIndex;
	if (v_command[1] == "*")
	{
		for (int j = 0; j < tableSource.schema.size(); j++)
		{
			inputSchemaIndex.push_back(j);
			SchemaItem sctemp;
			sctemp = tableSource.schema[j];
			schemaRusult.push_back(sctemp);
		}
	}
	else
	{
		for (int i = 0; i < fromIndex - 1; i++)
		{
			string schemaName;
			schemaName = v_command[i + 1];
			if (schemaName.find(',') != string::npos)
			{
				schemaName = schemaName.substr(0, schemaName.length() - 1);
			}
			for (int j = 0; j < tableSource.schema.size(); j++)
			{
				if (schemaName == tableSource.schema[j].name)
				{
					inputSchemaIndex.push_back(j);
					SchemaItem sctemp;
					sctemp = tableSource.schema[j];
					schemaRusult.push_back(sctemp);
				}


			}
		}
	}

	if (whereIndex == -1)
	{
		for (int i = 0; i < tableSource.rows.size(); i++)
		{
			Row tempR;
			for (int j = 0; j < inputSchemaIndex.size(); j++)
			{
				tempR.values.push_back(tableSource.rows[i].values[inputSchemaIndex[j]]);
			}
			rowsRusult.push_back(tempR);
		}
	}
	else
	{
		vector<string> conditionVector;
		for (int i = whereIndex + 1; i < v_command.size(); i++)
		{
			conditionVector.push_back(v_command[i]);
		}

		for (int i = 0; i < tableSource.rows.size(); i++)
		{
			if (testCondition(tableSource.schema, tableSource.rows[i], conditionVector))
			{
				Row tempR;
				for (int j = 0; j < inputSchemaIndex.size(); j++)
				{
					tempR.values.push_back(tableSource.rows[i].values[inputSchemaIndex[j]]);
				}
				rowsRusult.push_back(tempR);
			}
		}
	}

	result.rows = rowsRusult;
	result.schema = schemaRusult;

	return result;
}


bool CommandInterpreter::testCondition(vector<SchemaItem> schema, Row theRow, std::vector<std::string> conditionVector)
{
	bool result = false;

	string schName = conditionVector[0];
	string opration = conditionVector[1];
	string schValue = conditionVector[2];

	if (schValue.find(',') != string::npos)
	{
		schValue = schValue.substr(0, schValue.length() - 2);
	}
	if (schValue.find('\'') != string::npos)
	{
		schValue = schValue.substr(1, schValue.length() - 2);
	}
	if (schValue.find('\"') != string::npos)
	{
		schValue = schValue.substr(1, schValue.length() - 2);
	}

	if (opration == "=")
	{
		for (int i = 0; i < schema.size(); i++)
		{
			if ((schema[i].name == schName) && (theRow.values[i] == schValue))
			{
				result = true;
				break;
			}
		}
	}
	else if (opration == "<")
	{
		for (int i = 0; i < schema.size(); i++)
		{
			if ((schema[i].name == schName) && (theRow.values[i] < schValue))
			{
				result = true;
				break;
			}
		}
	}
	else if (opration == "<=")
	{
		for (int i = 0; i < schema.size(); i++)
		{
			if ((schema[i].name == schName) && (theRow.values[i] <= schValue))
			{
				result = true;
				break;
			}
		}
	}
	else if (opration == ">")
	{
		for (int i = 0; i < schema.size(); i++)
		{
			if ((schema[i].name == schName) && (theRow.values[i] > schValue))
			{
				result = true;
				break;
			}
		}
	}
	else if (opration == ">=")
	{
		for (int i = 0; i < schema.size(); i++)
		{
			if ((schema[i].name == schName) && (theRow.values[i] >= schValue))
			{
				result = true;
				break;
			}
		}
	}
	else if (opration == "!=")
	{
		for (int i = 0; i < schema.size(); i++)
		{
			if ((schema[i].name == schName) && (theRow.values[i] != schValue))
			{
				result = true;
				break;
			}
		}
	}

	int andIndex = -1;
	int orIndex = -1;
	for (int i = 0; i < conditionVector.size(); i++)
	{
		if (conditionVector[i] == "and")
		{
			andIndex = i;
			break;
		}
		if (conditionVector[i] == "or")
		{
			orIndex = i;
			break;
		}
	}

	if (andIndex != -1)
	{
		vector<string> conIn;
		for (int i = 4; i < conditionVector.size(); i++)
		{
			conIn.push_back(conditionVector[i]);
		}
		return (result && testCondition(schema, theRow, conIn));
	}
	else if (orIndex != -1)
	{
		vector<string> conIn;
		for (int i = 4; i < conditionVector.size(); i++)
		{
			conIn.push_back(conditionVector[i]);
		}
		return (result || testCondition(schema, theRow, conIn));
	}
	else if ((andIndex == -1) && (orIndex == -1))
	{
		return result;
	}
}

Table CommandInterpreter::naturalInnerProduct(std::string tableName1, std::string tableName2)
{
	Table result;
	vector<Row> rowsRusult;
	vector<SchemaItem> schemaRusult;

	Table *table1;
	Table *table2;

	if (this->database->getTable(tableName1)->rows.size() > this->database->getTable(tableName2)->rows.size())
	{
		table1 = this->database->getTable(tableName1);
		table2 = this->database->getTable(tableName2);
	}
	else
	{
		table1 = this->database->getTable(tableName2);
		table2 = this->database->getTable(tableName1);
	}

	int sameSch[2];
	for (int i = 0; i < table1->schema.size(); i++)
	{
		for (int j = 0; j < table2->schema.size(); j++)
		{
			if (table1->schema[i].name == table2->schema[j].name)
			{
				sameSch[0] = i;
				sameSch[1] = j;
				break;
			}
		}
	}

	for (int i = 0; i < table1->schema.size(); i++)
	{
		SchemaItem itemTemp;
		itemTemp.name = table1->schema[i].name;
		itemTemp.type = table1->schema[i].type;
		schemaRusult.push_back(itemTemp);
	}
	for (int i = 0; i < table2->schema.size(); i++)
	{
		if (i == sameSch[1])
			continue;
		SchemaItem itemTemp;
		itemTemp.name = table2->schema[i].name;
		itemTemp.type = table2->schema[i].type;
		schemaRusult.push_back(itemTemp);
	}

	for (int i = 0; i < table1->rows.size(); i++)
	{
		int cri = 0;
		Row rowTemp;
		for (int j = 0; j < table2->rows.size(); j++)
		{
			if (table1->rows[i].values[sameSch[0]] == table2->rows[j].values[sameSch[1]])
			{
				cri = 1;
				for (int m = 0; m < table1->rows[i].values.size(); m++)
				{
					rowTemp.values.push_back(table1->rows[i].values[m]);
				}
				for (int m = 0; m < table2->rows[j].values.size(); m++)
				{
					if (m == sameSch[1])
						continue;
					rowTemp.values.push_back(table2->rows[j].values[m]);
				}
			}
		}
		if (cri == 1)
		{
			rowsRusult.push_back(rowTemp);
		}
	}

	result.rows = rowsRusult;
	result.schema = schemaRusult;

	return result;
}

void CommandInterpreter::deleteRow(std::vector<std::string> v_command)
{
	string tableName = v_command[2];
	Table tableSours;

      int find = findTable(tableName);

      if (find == 0){ //找不到这个表
            cout << "Error: The table " << tableName <<  " does not exist in the database" << endl;
            return;
      }

	tableSours = *(this->database->getTable(tableName));

	int whereIndex = -1;
	string temp;
	for (int i = v_command.size() - 1; i >= 0; i--)
	{
		temp = v_command[i];
		for (int j = 0; j < temp.length(); j++){
			temp[j] = tolower(temp[j]);
		}
		// if (v_command[i].find("where") != string::npos)
		if (temp.find("where") != string::npos)
		{
			whereIndex = i;
			break;
		}
	}

	if (whereIndex == -1)
	{
		while (tableSours.rows.size() > 0)
		{
			tableSours.rows.pop_back();
		}
	}
	else
	{
		vector<string> conditionVector;
		for (int i = whereIndex + 1; i < v_command.size(); i++)
		{
			conditionVector.push_back(v_command[i]);
		}

		vector<Row>::iterator itor;
		for (itor = tableSours.rows.begin(); itor != tableSours.rows.end();)
		{
			if (testCondition(tableSours.schema, *itor, conditionVector))
			{
				itor = tableSours.rows.erase(itor);
			}
			else
			{
				itor++;
			}
		}
	}

	this->database->removeTable(tableName);
	this->database->addTable(tableSours);
    printf("Delete row process completed.\n");
}

/*
guess the input of the user,
for example, if user make a typo: "crate table",
the databse system will ask the user whether he/she means "create table"
*/
void CommandInterpreter::spellingErrorCorrection(std::vector<std::string> *v_command)
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
	std::string i = "/*";
	std::string j = "quit";
    std::string k = "delete";

	int a1 = lcs(a, b);
	int a2 = lcs(a, c);
	int a3 = lcs(a, d);
	int a4 = lcs(a, e);
	int a5 = lcs(a, f);
	int a6 = lcs(a, g);
	int a7 = lcs(a, h);
	int a8 = lcs(a, i);
      int a9 = lcs(a, j);
      int a10 = lcs(a, k);

	printf("Error: Invalid command. Please try again.\n");

	if (a1 >= 4)
	{
		cout << "Do you want to type in command 'select table'?" << endl;
		
	}
	else if (a2 >= 4)
	{
		cout << "Do you want to type in command 'create table'?" << endl;
	}
	else if (a3 >= 3)
	{
		cout << "Do you want to type in command 'exit'?" << endl;
	}
	else if (a4 >= 4)
	{
		cout << "Do you want to type in command 'insert into'?" << endl;
	}
	else if (a5 >= 3)
	{
		cout << "Do you want to type in command 'load'?" << endl;
	}
	else if (a6 >= 3)
	{
		cout << "Do you want to type in command 'print'?" << endl;
	}
	else if (a7 >= 3)
	{
		cout << "Do you want to type in command 'help'?" << endl;
	}
	// else if ((a == "/") || (a == "//") || (a == "#"))
    else if (a8 >= 1)
	{
		cout << "Do you want to write comments? Please use '/*' to begin with your comments, and '*/' to end your comments."<< endl;
	}
      else if (a9 >= 3)
	{
		cout << "Do you want to type in command 'quit'?" << endl;
	}
      else if (a10 >= 4)
	{
		cout << "Do you want to type in command 'delete table' or 'delete from'?" << endl;
	}
	cout << "Type in 'help' or 'h' for more help." << endl;
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

