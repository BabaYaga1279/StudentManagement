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
	int const width[5] = { 5, 11, 20, 13, 12 };
	FileReader filereader;
	CSVFile ClassNameList;
	LinkedList<CSVFile> ClassList;

	~ClassUtilities() {
		filereader.Write(ClassUti, ClassNameList);
		for (int i = 0; i < ClassNameList.x; ++i) {
			filereader.Write(ClassNameList.data[i][0], ClassList.GetAt(i)->data);
		}
		ClassList.Delete();
		ClassNameList.Delete();
	}


	ClassUtilities() {
		filereader.Read(ClassUti, ClassNameList);
		for (int i = 0; i < ClassNameList.x; ++i) {
			CSVFile ClassT;
			filereader.Read(ClassNameList.data[i][0], ClassT);
			ClassList.Push(ClassT);
		}
	}
	void DeleteClass(string filename) {
		int row, col;
		if (!ClassNameList.Find(filename, row, col)) return;
		ClassNameList.RemoveRow(row);
		auto T = ClassList.GetAt(row);
		ClassList.Pop(T);
	}
	void ImportNewClass(string filename) {
		if (ClassNameList.Find(filename)) DeleteClass(filename);
		CSVFile NewClass;
		filereader.Read(filename, NewClass);
		ClassList.Push(NewClass);
		ClassNameList.AddRow(filename);
	}
	void PrintClassList() {
		cout << ClassNameList.x << " classes total: " << endl;
		for (int i = 0; i < ClassNameList.x; ++i) cout << i << " : " << ClassNameList.data[i][0] << endl;
	}
	void PrintClass(string filename) {
		int x, y;
		if (!ClassNameList.Find(filename, x, y)) {
			cout << "Class " << filename << " not found !" << endl;
			return;
		}
		CSVFile Tmp = ClassList.GetAt(x) != nullptr ? ClassList.GetAt(x)->data : CSVFile();
		for (int i = 0; i < Tmp.x; ++i) {
			for (int j = 0; j < Tmp.y; ++j) cout << setw(width[j]) << Tmp.data[i][j] << ' ';
			cout << endl;
		}

	}
};

#endif