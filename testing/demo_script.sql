load students ;
load enrolled ;
load schedule ;
/* What are the names and SIDS of all students whose last name is 'Chan'? */
select SID, Firstname from students where Lastname = 'Chan';
/* Who took the course with CCN 21001, and what were their grades? */
select Firstname, Lastname, Grade from students, enrolled where CCN = '21001';
/* Who has taken the course named 61A from EECS? */
/* First, create a table that contains SIDs and course names */
create table enrolled2 as select SID from enrolled, schedule where Dept = 'EECS' and Num = '61A';
/* Print these SIDs */
print enrolled2;
/* Now print the names of the students in this list */
-- Does not work for now
-- select Firstname, Lastname from students, enrolled2;
quit 