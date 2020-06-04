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

	PrintCSVFile(file.FileNameList);

	file.CreateNewFolder("TEST3");

	file.CreateNewFolder("TEST4");

	file.RemoveFolder("TEST4");

	file.SubTail->CreateNewFolder("TESTB");

	file.CreateNewFolder("TEST4");

	file.SubTail->CreateNewFolder("TESTC");

	file.Delete();     

	return 0;
}