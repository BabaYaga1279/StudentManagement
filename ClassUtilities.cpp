#include "ClassUtilities.h"

ClassUtilities::~ClassUtilities() {
	filereader.Write(ClassUti, ClassNameList);
	for (int i = 0; i < ClassNameList.x; ++i) filereader.Write(ClassNameList.data[i][0], ClassList.GetAt(i)->data);
	for (int i = 0; i < ClassNameList.x; ++i) ClassList.GetAt(i)->data.Delete();
	ClassList.Delete();
	ClassNameList.Delete();
}

ClassUtilities::ClassUtilities() {
	filereader.Read(ClassUti, ClassNameList);
	for (int i = 0; i < ClassNameList.x; ++i) {
		CSVFile ClassT;
		filereader.Read(ClassNameList.data[i][0], ClassT);
		ClassList.Push(ClassT);
	}
}

void ClassUtilities::DeleteClass(string filename) {
	int row, col;
	if (!ClassNameList.Find(filename, row, col)) return;
	ClassNameList.RemoveRow(row);
	auto T = ClassList.GetAt(row);
	ClassList.Pop(T);
}
void ClassUtilities::ImportNewClass(string filename) {
	if (ClassNameList.Find(filename)) DeleteClass(filename);
	CSVFile NewClass;
	filereader.Read(filename, NewClass);
	ClassList.Push(NewClass);
	ClassNameList.AddRow(filename);
}
void ClassUtilities::PrintClassList() {
	cout << ClassNameList.x << " classes total: " << endl;
	for (int i = 0; i < ClassNameList.x; ++i) cout << i << " : " << ClassNameList.data[i][0] << endl;
}
void ClassUtilities::PrintClass(string filename) {
	int x, y;
	if (!ClassNameList.Find(filename, x, y)) {
		cout << "Class " << filename << " not found !" << endl;
		return;
	}
	CSVFile Tmp = ClassList.GetAt(x) != nullptr ? ClassList.GetAt(x)->data : CSVFile();
	width[0] = 4;
	width[1] = 4;
	width[2] = 4;
	width[3] = 4;
	width[4] = 4;
	width[5] = 4;
	width[6] = 4;
	for (int i = 0; i < Tmp.x; ++i)
		for (int j = 0; j < Tmp.y; ++j) if (width[j] <= Tmp.data[i][j].length()) width[j] = Tmp.data[i][j].length() + 2;

	for (int i = 0; i < Tmp.x; ++i) {
		for (int j = 0; j < Tmp.y; ++j) cout << setw(width[j]) << Tmp.data[i][j] << ' ';
		cout << endl;
	}

}
void ClassUtilities::AddStudent(string filename, string Student, bool Check, int row, int col) {
	if (!Check && !ClassNameList.Find(filename, row, col)) {
		return;
	}
	ClassList.GetAt(row)->data.AddRow(Student);
}
void ClassUtilities::AddStudent(string filename, string No, string StudentID, string Lastname, string Firstname, string Gender, string Dob, bool Check) {
	int row, col;
	if (!ClassNameList.Find(filename, row, col)) {
		return;
	}
	Check = true;
	if (No == "") {
		int x;
		x = ClassList.GetAt(row)->data.x;
		No = IntToString(x);
	}

	AddStudent(filename, No + ',' + StudentID + ',' + Lastname + ',' + Firstname + ',' + Gender + ',' + Dob, Check, row, col);
}

void ClassUtilities::RemoveStudent(string filename, int row, bool Check, int x, int y) {
	if (row == 0) return;
	if (!Check && !ClassNameList.Find(filename, x, y)) {
		cout << "Can't find " << filename << endl;
		return;
	}
	CSVFile Tmp = ClassList.GetAt(x)->data;
	if (row >= Tmp.x) {
		cout << "Can't delete Course " << row << endl;
		return;
	}

	ClassList.GetAt(x)->data.RemoveRow(row);
}

void ClassUtilities::RemoveStudent(string filename, string S) {
	int x, y;
	if (!ClassNameList.Find(filename, x, y)) {
		cout << "Can't find " << filename << endl;
		return;
	}
	int row, col;
	CSVFile Tmp = ClassList.GetAt(x)->data;
	if (!Tmp.Find(S, row, col)) {
		cout << S << " doesn't exist" << endl;
		return;
	}
	RemoveStudent(filename, row, true, x, y);
}