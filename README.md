# Student Management Application

by Bui Quang Minh and Pham Minh Duc
====================================
CS162 - Programming Techniques – Final project – Student management system Class: 19APCS1-2, 19CLC1-2-5-7-9-10 
Use-cases 
● All roles 
1. Login 
2. Show menu 
3. View profile info 
4. Change password 
5. Logout 

● Academic staff Class 
6. Import students of a class such as 18CLC6 from a csv file.  
▪ The csv file should include columns such as No (1), Student ID (18125001), Lastname (Nguyen Van), Firstname (A), Gender (Male), DoB (2000-04-01).  
▪ Remember to create student accounts based on their Student ID and their DoB. 
7. Manually add a new student to a class.  
▪ For example, there is a new student enrolled in 18CLC6. 
▪ Remember to create a student account based on his/her Student ID and their DoB. 
8. Edit an existing student. 
9. Remove a student. 
10. Change students from class A to class B 
11. View list of classes. 
12. View list of students in a class. Course 
13. Create / update / delete / view academic years (2018-2019), and semesters (Fall). 
14. From a semester, import courses such as CTT008, CTT010 from a csv file.  
▪ The csv file should include columns such as No (1), Course ID (CTT008), Course Name (Programming Techniques), Class (18CLC6), LecturerAccount (nhminh), Start Date (2019-01-07), End Date (2019-04-13), Day of Week (Wed), Start Hour:Minute (08:00), and End Hour:Minute (11:00), Room (I33).  
▪ By default, all students in the mentioned classes will be enrolled to imported courses. 
15. Manually add a new course. 
16. Edit an existing course. 
17. Remove a course. 
18. Remove a specific student from a course.
 
▪ For example, by default all students of 18CLC are enrolled in course CTT008, but because of a private reason, student Nguyen Van A is dropped from CTT008. 
19. Add a specific student to a course. 

▪ For example, student 1753001 enrolls in CTT008 to improve his previous result. 
 
20. View list of courses in the current semester. 
21. View list of students of a course. 
22. View attendance list of a course. 
23. Create / update / delete / view all lecturers. Scoreboard: 
24. Search and view the scoreboard of a course. 
25. Export a scoreboard to a csv file. Attendance list: 
26. Search and view attendance list of a course. 
27. Export a attendance list to a csv file. 

● Lecturer: 
28. View list of courses in the current semester. 
29. View list of students of a course.  
30. View attendance list of a course. 
31. Edit an attendance.  
32. Import scoreboard of a course (midterm, final, lab, bonus) from a csv file. 
33. Edit grade of a student 
34. View a scoreboard 

● Student: 
35. Check-in. 
36. View check-in result. 
37. View schedules. 
38. View his/her scores of a course. 