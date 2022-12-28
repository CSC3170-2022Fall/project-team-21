# Testing

Here we provide a unit test module and SQL scripts for testing. For more about the unit test, please refer to [this link](unit_test/README.md)

## How to test
Copy the contents of the .sql files into the command line where our app is running.

## What we have tested
We have thoroughly tested the `.sql` files in this folder and guarantee the robustness and correctness of our DB under these SQL commands. In the sql commands, we have included varieties of patterns, including changing to uppercase, testing join operations and so on to make them as thorough as possible.

These tests themselves can be made a demo for a simple university database containing information about students' information, course schedules, and the courses the students are in.

Our typical test starts first with the `create table` command by pasting all lines in the `create_table.sql` file into the CLI. Then, we can insert data by pasting all lines in the `insert_into.sql`. At any time, we can examine a table by using `print table <table_name>` or `select * from <table_name>`.

Further to the tests listed here, we have also tested various commands such that even under some incorrect commands or accessing tables that do not exist, our program won't crash.