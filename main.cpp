#include <iostream>
#include <iomanip>
#include <windows.h>

#include "FileReader.h"
#include "Utilities.h"
#include "CSVFile.h"
#include "CSVFileGroup.h"

class FileManager {
private:
	FileReader filereader;

public:
	string FileDir = "";
	CSVFile file_list;
	CSVFileGroup csv_list;

	FileManager(string FileDir = "") {
		this->FileDir = FileDir;
		filereader = FileReader(FileDir);

		filereader.Read("FolderList.csv", file_list);
		csv_list  = CSVFileGroup("CSVFileList.csv",filereader);

	}

	void ImportNewCSVFile(string filename, string FileDir = "") {
		filereader.ChangeDir(FileDir);

		csv_list.ImportNewFile(filename, filereader);
	}
	
	void CreateNewFolder(string filename, bool Override = false) {
		string dir = filename;

		if (dir.find(FileDir) == string::npos) dir = FileDir + dir;

		if (CreateDirectory(dir.c_str(), NULL)) {
			cerr << dir << " created !" << endl;
		}
		else if (ERROR_ALREADY_EXISTS == GetLastError()) {
			cerr << dir << " aready exits !" << endl;
			if (Override) RemoveFolder(filename);
			if (file_list.Find(filename)) return;
		}
		else {
			cerr << "Can't create folder" << endl;
			return;
		}

		file_list.AddRow(filename);
	}

	void RemoveFolder(string filename) {
		string dir = filename;

		if (dir.find(FileDir) == string::npos) dir = FileDir + dir;

		if (RemoveDirectory(dir.c_str())) {
			cerr << dir << " deleted !" << endl;
		}
		else {
			cerr << "Can't delete folder" << endl;
			return;
		}

		int x, y;
		if (file_list.Find(filename,x,y)) file_list.RemoveRow(x);
	}

	void Delete() {
		filereader.ChangeDir(FileDir);

		filereader.Write("FolderList.csv", file_list);
		file_list.Delete();

		csv_list.Delete(filereader);
	}

};

int main() {
	FileManager file("TEST0/");

	PrintCSVFile(file.file_list);

	file.csv_list.PrintFileNameList();
	
	file.csv_list.PrintOneFile("TEST1.csv");  

	file.CreateNewFolder("TEST1");

	file.CreateNewFolder("TEST2");

	file.Delete();  

	FileManager file2("TEST0/TEST1/");

	file2.Delete();
	return 0;
}