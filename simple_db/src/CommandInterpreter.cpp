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

				// no ; found: part of the command
				printf("> ");
				getline(cin, command);
				vector<std::string> tmp_v_command;
				command_continue = true;
				tmp_v_command = tokenizer(command);
				v_command.insert(v_command.end(), tmp_v_command.begin(), tmp_v_command.end());

				// printf("You need to have a semicolumn(;) at the end of your input. Please input again.\n");
				
				// fflush(stdout);
			}
		}
	}

	return get_command;
}

void CommandInterpreter::execute(vector<std::string> v_command, Database *db)
// void CommandInterpreter::execute(std::string command, Database *db)
{
	this->database = db;
	// std::vector<std::string> v_command = tokenizer(command);

	// for (int i = 0; i < v_command.size(); i++) {
	//       cout << v_command[i] << " ";
	// }

	// cout << endl;

	if (v_command.size() == 0)
	{
		return;
	}

	// convert the first token to lowercase
	std::transform(v_command[0].begin(), v_command[0].end(), v_command[0].begin(), ::tolower);

	if (v_command[0] == "select")
	{
		// first find the index of "from"
		int idx_of_from;
		printf("Search results:\n");
		Table tb = select(v_command);
		tb.printOut();
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
		if (v_command[1] == "table")
		{
			deleteTable(&v_command);
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
		// if (v_command.len)
		// {

		// }

		printTable(&v_command);
	}
	else if (v_command[0] == "exit" || v_command[0] == "q" || v_command[0] == "quit")
	{
		// first save to file, then return
		exitCommand();
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
	}
	else
	{
		spellingErrorCorrection(&v_command);
		// printf("Invalid command, please try again.\n");
		// guessUserInput(v_command); // guess the input of the user
		// 也可以使用spellingErrorCorrection实现拼写错误的改正与纠错。
	}
}

int CommandInterpreter::checkTokenNumber(vector<std::string> v_command)
{
	if (v_command[0] == "select")
	{
	}
	else if (v_command[0] == "create")
	{
	}
	else if (v_command[0] == "delete")
	{
	}
	else if (v_command[0] == "insert")
	{
	}
	else if (v_command[0] == "load")
	{
	}
	else if (v_command[0] == "store")
	{
	}
	else if (v_command[0] == "print")
	{
	}
	else if (v_command[0] == "exit" || v_command[0] == "q" || v_command[0] == "quit")
	{
	}
	else if (v_command[0] == "help" || v_command[0] == "h")
	{
	}
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

void CommandInterpreter::store(std::vector<std::string> *v_command)
{
	// store <table name>;
	string tableName = v_command->at(1);
	Table *tb = this->database->getTable(tableName);
	if (tb == NULL)
	{
		printf("Table %s does not exist.\n", tableName.c_str());
		return;
	}
	tb->saveToFile(tb->name);
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

	// get the pos of "values" or "VALUES"
	int pos = 0;
	for (int i = 0; i < v_command->size(); i++)
	{
		if (v_command->at(i) == "values" || v_command->at(i) == "VALUES")
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
			return;
		}
	}
	if (idx == -1)
	{ // the table we search is not found
		printf("Error: The target table does not exist in this database.\n");
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

	// name already exists
	Table *target_table = this->database->getTable(tableName);
	if (target_table != NULL)
	{
		printf("Error: The name of the table you want to create already exists in this database.\n", tableName.c_str());
		return;
	}

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

	// delete the "as"
	if (v_command->at(3) == "as")
	{
		v_command->erase(v_command->begin() + 3);
	}

	if (v_command->at(3) == "select")
	{
		// create v_command copy starting from 4
		vector<string> v_command_copy;
		for (int i = 3; i < v_command->size(); i++)
		{
			v_command_copy.push_back(v_command->at(i));
		}
		Table tb = select(v_command_copy);
		tb.name = tableName;
		this->database->tables.push_back(tb);
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
}

void CommandInterpreter::printTable(std::vector<std::string> *v_command)
{
	string target_table_name = v_command->at(1);
	Table *target_table = this->database->getTable(target_table_name);

	if (target_table != NULL)
	{
		printf("Contents of %s\n", target_table->name.c_str());
		target_table->printOut();
	}
	else
	{ // we cannot find the table we want to print in the database
		cout << "Error: Cannot find the table: " << target_table_name << endl;
	}
}

int CommandInterpreter::findTable(string tableName)
{
	Table *target_table = this->database->getTable(tableName);
	if (target_table != NULL)
	{ // 找不到这个table
		printf("Error: The name of the table you want to create already exists in this database.\n", tableName.c_str());
		return 0;
	}
	else
	{
		return 1;
	}
}

Table CommandInterpreter::select(std::vector<std::string> v_command)
{
	// fill in
	Table result;
	vector<Row> rowsRusult;
	vector<SchemaItem> schemaRusult;

	int fromIndex;
	for (int i = 1; i < v_command.size(); i++)
	{
		if (v_command[i].find("from") != string::npos)
		{
			fromIndex = i;
			break;
		}
	}
	int whereIndex = -1;
	for (int i = v_command.size() - 1; i >= 0; i--)
	{
		if (v_command[i].find("where") != string::npos)
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
		for (int i = fromIndex + 1; i < whereIndex; i++)
		{
			string temp = v_command[i];
			if (temp.find(')') != string::npos)
			{
				temp = temp.substr(0, temp.length() - 1);
			}
			input.push_back(temp);
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
	tableSours = *(this->database->getTable(tableName));

	int whereIndex = -1;
	for (int i = v_command.size() - 1; i >= 0; i--)
	{
		if (v_command[i].find("where") != string::npos)
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
	// std::string j = "select";

	int a1 = lcs(a, b);
	int a2 = lcs(a, c);
	int a3 = lcs(a, d);
	int a4 = lcs(a, e);
	int a5 = lcs(a, f);
	int a6 = lcs(a, g);
	int a7 = lcs(a, h);
	// int a8 = lcs(a, i);

	printf("    Error: Invalid command. Please try again.\n");

	if (a1 >= 4)
	{
		cout << "    Do you want to type in command 'select table'?" << endl;
		// first find the index of "from"
		int idx_of_from;
		// parse(command[idx_of_from:])  // TODO
	}
	else if (a2 >= 3)
	{
		cout << "    Do you want to type in command 'create table'?" << endl;
		// createTable(&v_command);
	}
	else if (a3 >= 3)
	{
		cout << "    Do you want to type in command 'exit'?" << endl;
		// exitCommand();
	}
	else if (a4 >= 4)
	{
		cout << "    Do you want to type in command 'insert into'?" << endl;
		// insertCommand(&v_command);
	}
	else if (a5 >= 3)
	{
		cout << "    Do you want to type in command 'load'?" << endl;
		// this->load(v_command);
	}
	else if (a6 >= 3)
	{
		cout << "    Do you want to type in command 'print'?" << endl;
		// printTable(&v_command);
	}
	else if (a7 >= 3)
	{
		cout << "    Do you want to type in command 'help'?" << endl;
		// printf("Help message here\n");
	}
	else if ((a == "/") || (a == "//") || (a == "#"))
	{
		cout << "    Do you want to write comments? Please use '/*' to begin with your comments.\n"
			 << endl;
	}
	cout << "   Type in 'help' or 'h' for more help." << endl;
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

/*
guess the input of the user,
for example, if user make a typo: "crate table",
the databse system will ask the user whether he/she means "create table"
*/
// void CommandInterpreter::guessUserInput(std::vector<std::string> v_command)
// {
//       string input;
//       input = v_command[0].substr(0, 2);
//       if (input == "cr")
//       {
//             printf("Do you mean command 'create table'?\n");
//       }
//       else if (input == "lo")
//       {
//             printf("Do you mean command 'load'?\n");
//       }
//       else if (input == "st")
//       {
//             printf("Do you mean command 'store'?\n");
//       }
//       else if (input == "in")
//       {
//             printf("Do you mean command 'insert into'?\n");
//       }
//       else if (input == "pr")
//       {
//             printf("Do you mean command 'print'?\n");
//       }
//       else if (input == "qu")
//       {
//             printf("Do you mean command 'quit'?\n");
//       }
//       else if (input == "ex")
//       {
//             printf("Do you mean command 'exit'?\n");
//       }
//       else if (input == "se")
//       {
//             printf("Do you mean command 'select'?\n");
//       }
//       else if (input == "//")
//       {
//             printf("Do you want to make comments? Please use '/*' to begin with your commands.\n");
//       }
//       printf("Type in 'help' or 'h' for more help.\n");
// }
