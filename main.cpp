#include <iostream>
#include <iomanip>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

#include "FileReader.h"
#include "Utilities.h"
#include "CSVFile.h"
#include "CSVFileGroup.h"
#include "Folder.h"
#include "UI.h"

using namespace std;


int main() {
	
	Folder file("DATA/");
	Folder* profile;
	file.PrintAllSubFolder();
	_getch();

	while (true) {
		Login(file, profile);
		if (profile != nullptr)
		if (profile->FileDir.find("Staff") != string::npos) Staff(file, profile);
		else if (profile->FileDir.find("Lecturer") != string::npos) Lecturer(file, profile);
		else Student(file, profile);

		file.PrintAllSubFolder();

		cout << "\n\n Press Esc to exit or any key to continue .\n";
		char key = _getch();
		if (key == 27) break;
	}


	file.Delete();     

	return 0;
}