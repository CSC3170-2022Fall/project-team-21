[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=9475714&assignment_repo_type=AssignmentRepo)
# CSC3170 Course Project

## Task allocation for team members
Maintainers:

Due date: Dec11 23:59pm. However you should finish it as soon as possible!
- `CommandInterpreter.cpp`: 刘起，杨亮，李珈祺，maybe Yohanes assisting us.

Due date: Dec11 23:59pm. However you should finish it as soon as possible!
- `Database.cpp`: Yohanes

- `Table.cpp`:  连珈玮 & Yohanes


- `Row.cpp`: it is done.
- `SchemaItem.cpp`: it is done.
- `main.cpp`: This is how you test your implementation. This is the driver code for the application. You can modify it as you want, but the general structure done.
- `gui/`: Darren. Tentative GUI design and survey for our database.
- `testing/`: Yohanes. Provide test cases for our DB and also for demo.
- Abstract and report: 王茗萱 

## Message to our team members
<!-- This part should be deleted in the submission -->
This is Li Jiaqi writing to our teammates, here are some things you need to be cautious about out when collaborating in our group project, and the things that we should do to make our project better.

- Because we're **collaborating** instead of working on your own, please synchronize this git repository from time to time by using a `git pull`, or just click on the "synchronize" button at the left bar of vscode.

- Please write good commit message, clearly indicating what you've done. Do not commit unnecessary files or temporary files.



There are several timelines everyone should keep in mind:
- By December 4 23:30 pm we should submit:
    - Project abstract
    - Progress Report
- By December 11 23:30 pm:
    - Submit slides in presentation
    - Apply for presentation time slot
    - Upload video demo of our program

- By December 24 23:30 pm:
    - Submit report

As you can see we should finish most things, including our program before December 11, so hurry up!!!


## Project Overall Description

This is our implementation for the course project of CSC3170, 2022 Fall, CUHK(SZ). For details of the project, you can refer to [project-description.md](project-description.md). In this project, we will utilize what we learned in the lectures and tutorials in the course, and implement either one of the following major jobs:

<!-- Please fill in "x" to replace the blank space between "[]" to tick the todo item; it's ticked on the first one by default. -->

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
| 120090874  |  杨亮 | 120090874@link.cuhk.edu.cn            | YangBright|
| 120040022  | Darren Boesono         | 120040022@link.cuhk.edu.cn            | dboesono|
| 120040006  |Yohanes James   | 120040006@link.cuhk.edu.cn        | YohanesJames|
| 120090231  |王茗萱   | 3096968424@qq.com       | helloworldlgu|

## Project Specification

<!-- You should remove the terms/sentence that is not necessary considering your option/branch/difficulty choice -->

After thorough discussion, our team made the choice and the specification information is listed below:

- Our option choice is: **Option 3**
<!-- - Our branch choice is: **Branch 1**
- The difficulty level is: **Normal**

As for Option 2, our topic background specification can be found in [background-specification.md](background-specification.md). -->

## Project Abstract

<!-- TODO -->
We will choose option3 as our final project. In this project, we will write a miniature relational database management system (DBMS) that stores data tables, one of which consists of several (labeled) rows of information. In addition, our system will include a database query language similar to SQL to extract information from these tables.

We will mainly use C++ to implement our code. To implement the specific database and related methods, we divide it into a number of classes. The specific architecture we will adopt is as follows:

- `Row` class: serves as the underlying storage unit for information about tables in the database, recording row information.
- `SchemaItem` class: records tables’ schemas in the database.
- `Table` class: A data structure that stores tables in a database. It contains three attributes, the rows (`Row` class) to record the row information, the schema (`SchemaItem` class) to record the schema, and the database (`Database` class) to record the database which the table belongs. It also contains some methods, such as insert, print, delete.
- `CommandInterpreter` class: Used to accept and execute commands. Contains the specific implementation method of the command. (exit, select, help…)
- `Database` class: As a whole database, which contains instances of the Table and CommandInterpreter classes as attributes.

In the end, our database management system will realize two-way data transfer with .db file , create tables, insert rows into existing tables, print tables and other functions. In addition to this, we will implement Select clauses, which are used in select statements and in create statements. They denote tables whose information is selected from other tables. 
