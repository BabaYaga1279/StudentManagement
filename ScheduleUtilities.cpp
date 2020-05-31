#include "ScheduleUtilities.h"

ScheduleUtilities::ScheduleUtilities() {
	filereader.Read(ScheduleUti, ScheduleNameList);
	for (int i = 0; i < ScheduleNameList.x; ++i) {
		CSVFile Course;
		filereader.Read(ScheduleNameList.data[i][0], Course);
		ScheduleList.Push(Course);
	}
}
ScheduleUtilities::~ScheduleUtilities() {
	filereader.Write(ScheduleUti, ScheduleNameList);
	for (int i = 0; i < ScheduleNameList.x; ++i) filereader.Write(ScheduleNameList.data[i][0], ScheduleList.GetAt(i)->data);
	for (int i = 0; i < ScheduleNameList.x; ++i) ScheduleList.GetAt(i)->data.Delete();
	ScheduleNameList.Delete();
	ScheduleList.Delete();
}
void ScheduleUtilities::PrintScheduleNameList() {
	for (int i = 0; i < ScheduleNameList.x; ++i) {
		for (int j = 0; j < ScheduleNameList.y; ++j) cout << ScheduleNameList.data[i][j] << ' ';
		cout << endl;
	}
}
void ScheduleUtilities::PrintSchedule(string filename) {
	int x, y;
	if (!ScheduleNameList.Find(filename, x, y)) {
		cout << filename << " Not found" << endl;
		return;
	}

	CSVFile Tmp = ScheduleList.GetAt(x) != nullptr ? ScheduleList.GetAt(x)->data : CSVFile();

	for (int i = 0; i < 20; ++i) width[i] = 4;

	for (int i = 0; i < Tmp.x; ++i)
		for (int j = 0; j < Tmp.y; ++j) if (width[j] <= Tmp.data[i][j].length()) width[j] = Tmp.data[i][j].length() + 1;
	for (int i = 0; i < Tmp.x; ++i) {
		for (int j = 0; j < Tmp.y; ++j) cout << setw(width[j]) << Tmp.data[i][j] << ' ';
		cout << endl;
	}
}

void ScheduleUtilities::ImportNewSchedule(string filename) {
	if (ScheduleNameList.Find(filename)) DeleteSchedule(filename);
	CSVFile NewSchedule;
	filereader.Read(filename, NewSchedule);
	ScheduleList.Push(NewSchedule);
	ScheduleNameList.AddRow(filename);
}

void ScheduleUtilities::CreateCourse(string filename, string Course, bool Check, int row, int col) {
	if (!Check && !ScheduleNameList.Find(filename, row, col)) {
		cout << "Can not add course !" << endl;
		return;
	}
	ScheduleList.GetAt(row)->data.AddRow(Course);
}
void ScheduleUtilities::CreateCourse(string filename, string No, string CourseID, string CourseName,string ClassName, string LecturerAccount, string LN, string LD, string LG
									, string StartDay, string EndDay, string DayOfWeek, string StartH, string StartM, string EndH, string EndM, string Room) {
	if (CourseID == "") {
		cout << "Invalid Course ID" << endl;
		return;
	}
	if (CourseName == "") {
		cout << "Invalid Course Name" << endl;
		return;
	}

	int row, col;
	if (!ScheduleNameList.Find(filename, row, col)) {
		cout << filename << " not exist !" << endl;
		return;
	}

	CSVFile Tmp = ScheduleList.GetAt(row)->data;

	if (Tmp.Find(CourseID)) {
		cout << "Coure ID : " << CourseID << " Already exist !" << endl;
		return;
	}
	if (Tmp.Find(CourseName)) {
		cout << "Course Name : " << CourseName << " Already exist !" << endl;
		return;
	}
	if (No == "") {
		No = IntToString(Tmp.x);
	}
	string Course = No + ',' + CourseID + ',' + CourseName + ',' + ClassName +','+ LecturerAccount + ',' + LN + ',' + LD + ',' + LG
				+ ',' + StartDay + ',' + EndDay + ',' + DayOfWeek + ',' + StartH + ',' + StartM + ',' + EndH + ',' + EndM + ',' + Room + '\n';
	CreateCourse(filename, Course, true, row, col);
}

void ScheduleUtilities::DeleteSchedule(int row) {
	if (row >= ScheduleNameList.x) {
		cout << "Can't delete Schedule" << endl;
		return;
	}
	ScheduleList.GetAt(row)->data.Delete();
	ScheduleList.Pop(row);
}
void ScheduleUtilities::DeleteSchedule(string S) {
	int row, col;
	if (!ScheduleNameList.Find(S, row, col)) {
		cout << "Can't delete Schedule " << S << endl;
		return;
	}
	DeleteSchedule(row);
}
void ScheduleUtilities::DeleteCourse(string filename, int row, bool Check, int x, int y) {
	if (row == 0) return;
	if (!Check && !ScheduleNameList.Find(filename, x, y)) {
		cout << "Can't find " << filename << endl;
		return;
	}
	CSVFile Tmp = ScheduleList.GetAt(x)->data;
	if (row >= Tmp.x) {
		cout << "Can't delete Course " << row << endl;
		return;
	}

	ScheduleList.GetAt(x)->data.RemoveRow(row);
}
void ScheduleUtilities::DeleteCourse(string filename, string S) {
	int x, y;
	if (!ScheduleNameList.Find(filename, x, y)) {
		cout << "Can't find " << filename << endl;
		return;
	}
	int row, col;
	CSVFile Tmp = ScheduleList.GetAt(x)->data;
	if (!Tmp.Find(S, row, col)) {
		cout << S << " doesn't exist" << endl;
		return;
	}
	DeleteCourse(filename, row, true, x, y);
}
