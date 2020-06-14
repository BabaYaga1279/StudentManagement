#ifndef _UI_H_
#define _UI_H_
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

#include "Folder.h"

using namespace std;

void Login(Folder& file, Folder*& profile);
void EditProfile(Folder& file, Folder*& profile);

void Staff_ImportAClass(Folder& file);
void Staff_AddStudentToClass(Folder& file);
void Staff_EditStudent(Folder& file);
void Staff_RemoveStudent(Folder& file);
void Staff_ChangeStudentClass(Folder& file);
void Staff_PrintClassList(Folder& file);
void Staff_PrintStudentList(Folder& file);
void Staff_CreateAcademicYear(Folder& file);
void Staff_CreateSemester(Folder& file);
void Staff_ViewYearsAndSemester(Folder& file);
void Staff_ImportCourse(Folder& file);
void Staff_AddNewCourse(Folder& file);
void Staff_EditCourse(Folder& file);
void Staff_RemoveCourse(Folder& file);
void Staff_RemoveStudentFromCourse(Folder& file);
void Staff_AddStudentToCourse(Folder& file);
void Staff_PrintCourse(Folder& file);
void Staff_PrintCourseStudent(Folder& file);
void Staff_PrintCourseAttendance(Folder& file);
void Staff_ExportCourseAttendance(Folder& file);
void Staff_PrintLecturer(Folder& file);
void Staff_CreateLecturer(Folder& file);
void Staff_EditLecturer(Folder& file);
void Staff_RemoveLecturer(Folder& file);
void Staff_PrintScoreBoard(Folder& file);
void Staff_ExportScoreBoard(Folder& file);
void Staff(Folder& file, Folder*& profile);

void Student_CheckIn(Folder& file, Folder *& profile);
void Student_CheckInResult(Folder& file, Folder*& profile);
void Student_Schedule(Folder& file);
void Student_Score(Folder& file);
void Student(Folder& file, Folder*& profile);

void Lecturer_PrintCourseList(Folder& file, Folder *& profile);
void Lecturer_PrintCourseStudent(Folder& file, Folder*& profile);
void Lecturer_PrintCourseAttending(Folder& file, Folder*& profile);
void Lecturer_EditCourseAttending(Folder& file, Folder*& profile);
void Lecturer_ImportCourseScore(Folder& file, Folder*& profile);
void Lecturer_EditStudentScore(Folder& file, Folder*& profile);
void Lecturer_PrintAllScore(Folder& file, Folder*& profile);
void Lecturer(Folder& file, Folder*& profile);

#endif