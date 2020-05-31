#ifndef _ScheduleUtilities_H_
#define _ScheduleUtilities_H_

#include <iostream>
#include <iomanip>
#include "CSVFile.h"
#include "Utilities.h"
#include "FileReader.h"

class ScheduleUtilities {
public:
	string const ScheduleUti = "ScheduleList.csv";
	int width[20] = { 5, 11, 30, 11, 20, 20, 20, 20, 20 };
	FileReader filereader;
	CSVFile ScheduleNameList;
	LinkedList<CSVFile> ScheduleList;

	ScheduleUtilities();
	~ScheduleUtilities();

	void PrintScheduleNameList();
	void PrintSchedule(string filename);
	void ImportNewSchedule(string filename);
	void CreateCourse(string filename, string Course, bool Check = false, int row = -1, int col = -1);
	void CreateCourse(string filename, string No = "", string CourseID = "", string CourseName = "", string ClassName = "",string LecturerAccount = "", string LN = "", string LD = "", string LG = ""
					, string StartDay = "", string EndDay = "", string DayOfWeek = "", string StartH = "", string StartM = "", string EndH = "", string EndM = "", string Room = "");
	void DeleteSchedule(int row);
	void DeleteSchedule(string S);
	void DeleteCourse(string filename, int row, bool Check = false, int x = -1, int y = -1);
	void DeleteCourse(string filename, string S);
};

#endif