#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "CSVFile.h"
#include "FileReader.h"
#include "Utilities.h"

using namespace std;

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