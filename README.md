[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=9475714&assignment_repo_type=AssignmentRepo)
# CSC3170 Course Project

## Project Overall Description

This is our implementation for the course project of CSC3170, 2022 Fall, CUHK(SZ). For details of the project, you can refer to [project-description.md](project-description.md). In this project, we will utilize what we learned in the lectures and tutorials in the course, and implement either one of the following major jobs:

- [ ] **Application with Database System(s)**
- [x] **Implementation of a Database System**

## Team Members

Our team consists of the following members, listed in the table below (the team leader is shown in the first row, and is marked with 🚩 behind his/her name):

<!-- change the info below to be the real case -->

| Student ID | Student Name | Email | Github Username |
| ---------- | ------------ | ------------------------- | -----------------------|
| 120090727  | 李珈祺 🚩      | 120090727@link.cuhk.edu.cn        |LJQ0727|
| 123010345  | 刘起         | 120090027@link.cuhk.edu.cn          |LittleShaco|
| 119030043  | 连珈玮         | 119030043@link.cuhk.edu.cn        |jlianxm|
| 120090874  |  杨亮 | 120090874@link.cuhk.edu.cn            | bright |
| 120040022  | Darren Boesono         | 120040022@link.cuhk.edu.cn            | dboesono|
| 120040006  |Yohanes James   | 120040006@link.cuhk.edu.cn        | YohanesJames|
| 120090231  |王茗萱   | 3096968424@qq.com       | helloworldlgu|

### Task allocation for team members
Please refer to [task-allocation.md](task-allocation.md) for the detailed task allocation throughout the process of building our project.

## Project Specification

<!-- You should remove the terms/sentence that is not necessary considering your option/branch/difficulty choice -->

After thorough discussion, our team made the choice and the specification information is listed below:

- Our option choice is: **Option 3**
<!-- - Our branch choice is: **Branch 1**
- The difficulty level is: **Normal**

As for Option 2, our topic background specification can be found in [background-specification.md](background-specification.md). -->

## Project Abstract

We will choose option3 as our final project. In this project, we will write a miniature relational database management system (DBMS) that stores data tables, one of which consists of several (labeled) rows of information. In addition, our system will include a database query language similar to SQL to extract information from these tables.

We will mainly use C++ to implement our code. To implement the specific database and related methods, we divide it into a number of classes. The specific architecture we will adopt is as follows:

- `Row` class: serves as the underlying storage unit for information about tables in the database, recording row information.
- `SchemaItem` class: records tables’ schemas in the database.
- `Table` class: A data structure that stores tables in a database. It contains three attributes, the rows (`Row` class) to record the row information, the schema (`SchemaItem` class) to record the schema, and the database (`Database` class) to record the database which the table belongs. It also contains some methods, such as insert, print, delete.
- `CommandInterpreter` class: Used to accept and execute commands. Contains the specific implementation method of the command. (exit, select, help…)
- `Database` class: As a whole database, which contains instances of the Table and CommandInterpreter classes as attributes.

In the end, our database management system will realize two-way data transfer with .db file , create tables, insert rows into existing tables, print tables and other functions. In addition to this, we will implement Select clauses, which are used in select statements and in create statements. They denote tables whose information is selected from other tables. 
