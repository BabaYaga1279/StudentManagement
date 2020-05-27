#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "CSVFile.h"
#include "FileReader.h"
#include "Utilities.h"

using namespace std;

class ClassUtilities {
private:
	string const ClassUti = "ClassList.csv";
	FileReader filereader;
	CSVFile ClassNameList;
	LinkedList<CSVFile> ClassList;

	ClassUtilities() {
		filereader.Read(ClassUti, ClassNameList);
		for (int i = 0; i < ClassNameList.x; ++i) {
			CSVFile ClassT;
			filereader.Read(ClassNameList.data[i][0], ClassT);
			ClassList.Push(ClassT);
		}
	}
	~ClassUtilities() {
		filereader.Write(ClassUti, ClassNameList);
		for (int i = 0; i < ClassNameList.x; ++i) {
			filereader.Write(ClassNameList.data[i][0], ClassList.GetAt(i)->data);
		}
		ClassList.Delete();
		ClassNameList.Delete();
	}
public:
	void DeleteClass(string filename) {
		int x, y;
		if (!ClassNameList.Find(filename, x, y)) return;

	}
	void ImportNewClass(string filename) {
		

	}
};

int main() {
	FileReader filereader;

	CSVFile lecturer;
	filereader.Read("accounts_lecturer.csv", lecturer);

	//lecturer.AddRow("teacher1,teacher1\n");
	//lecturer.SwapRow(2, 3);
	lecturer.SortByColume(0, true);
	lecturer.EditBlock(3, 1, "teacher3");
	PrintFileCSV(lecturer);

	filereader.Write("accounts_lecturer.csv", lecturer);
	lecturer.Delete();
	return 0;
}