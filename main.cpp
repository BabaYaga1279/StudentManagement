#include <iostream>
#include <iomanip>
#include <windows.h>

#include "FileReader.h"
#include "Utilities.h"
#include "CSVFile.h"
#include "CSVFileGroup.h"
#include "Folder.h"

int main() {
	Folder file("DATA/");

	PrintCSVFile(file.file_name_list);

	file.csv_list.PrintFileNameList();
	
	file.csv_list.PrintOneFile("TEST1.csv");  

	file.CreateNewFolder("TEST1");

	file.CreateNewFolder("TEST2");

	file.Delete();  

	return 0;
}