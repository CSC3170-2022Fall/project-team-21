select * from schedule;

select SID from enrolled;

select SID from students;

select CCN, Name, Room from schedule;

select SID from enrolled where CCN = '22100';

select SID from enrolled where CCN = '22101' and Grade != 'A';

/* Test the result of joining two tables */
select * from students, enrolled;

select Name, Grade, SID from students, enrolled where Major = "CSC";

select CCN, Name from  schedule where Room = '60 Evans';

select SID, Name from students where Age >=20;

