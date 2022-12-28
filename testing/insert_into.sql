insert into schedule values '22100', 'Math', '60 Evans';
insert into schedule values '22101', 'Science', '2050 VLSB';
insert into schedule values '22102', 'English', '1 Pimentel';

insert into students values '101', 'Jason', 'CSC', '20';
insert into students values '102', 'Valerie', 'Math', '25';

INSERT INTO students (
    SID (STRING), Name (STRING), Major (STRING), Age (INT)
    ) 
    values '103', 'Jonathan', 'EECS', '18';


insert into enrolled values '101', '22100', 'B';
insert into enrolled values '102', '22101', 'A';
insert into enrolled values '103', '22100', 'C';
insert into enrolled values '101', '22101', 'B-';
insert into enrolled values '102', '22102', 'C+';
insert into enrolled values "103", '22102', 'A';




