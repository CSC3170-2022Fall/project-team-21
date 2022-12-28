select * from schedule;

select SID from enrolled;

select SID from students;


select CCN, Name, Room from schedule;   

select SID from enrolled where CCN = '22100';    

select SID from enrolled where CCN = '22101' and Grade != 'A';  

select SID from enrolled where Grade = 'B' or Grade = 'A';

/* Test the result of natural inner join of two tables */
select * from students, enrolled;

SELECT Name, Grade, SID from students, enrolled where Major = "CSC";  

select CCN, Room from schedule where Name = "Math";

/* test for robustness, no column name Room in both tables */
select CCN, Room from enrolled, students where CCN = '22100';

select SID, Name from students where Age >= 20;
SELECT SID, Name FROM students WHERE Age >= 20;

