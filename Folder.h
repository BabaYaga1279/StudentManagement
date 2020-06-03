#ifndef _Folder_H_
#define _Folder_H_


#include <iostream>
#include <iomanip>
#include <windows.h>

#include "FileReader.h"
#include "CSVFile.h"
#include "CSVFileGroup.h"



class Folder {
private:
	FileReader filereader;

public:
	string FileDir = "";
	CSVFile file_name_list;

	CSVFileGroup csv_list;
	Folder();
	Folder(string FileDir = "");
	bool DirExist(string dir);
	void ImportNewCSVFile(string filename, string FileDir = "");
	void CreateNewFolder(string filename, bool Override = false);
	void RemoveFolder(string filename);
	void Delete();
};

#endif
