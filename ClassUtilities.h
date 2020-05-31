#ifndef _ClassUtilities_H_
#define _ClassUtilities_H_

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <iomanip>
#include "CSVFile.h"
#include "FileReader.h"
#include "Utilities.h"

using namespace std;

class ClassUtilities {
public:
	string const ClassUti = "ClassList.csv";
	int width[10] = { 5, 11, 15, 10, 13, 12 };
	FileReader filereader;
	CSVFile ClassNameList;
	LinkedList<CSVFile> ClassList;

	~ClassUtilities();
	ClassUtilities();

	void PrintClassList();
	void PrintClass(string filename);
	void ImportNewClass(string filename);
	void AddStudent(string Class, string Student, bool Check = false, int row = -1, int col = -1);
	void AddStudent(string Class, string No, string StudentID, string Lastname, string Firstname, string Gender, string Dob, bool Check = false);
	void DeleteClass(string filename);
	void RemoveStudent(string filename, int row, bool Check = false, int x = -1, int y = -1);
	void RemoveStudent(string filename, string S);
};

#endif