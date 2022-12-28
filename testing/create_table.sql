create table students as SID (STRING), Name (STRING), Major (STRING), Age (INT);
create table enrolled as SID (STRING), CCN (STRING), Grade (STRING);
create table schedule as CCN (STRING), Name (STRING), Room (STRING);

CREATE TABLE tester A(string), B(INTEGER);
create TABLE tester1 A(char(50)), B(NUMERIC);
create table enrolled2 as select SID from enrolled, schedule where Dept = 'EECS' and Num = '61A';
