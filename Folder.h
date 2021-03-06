#ifndef _Folder_H_
#define _Folder_H_

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <windows.h>
#include "FileReader.h"
#include "CSVFile.h"
#include "CSVFileGroup.h"

class Folder {
public:
	string FileDir = "";
	CSVFile FolderNameList;
	Folder *Next = nullptr, *Prev = nullptr;
	Folder *SubHead = nullptr, *SubTail = nullptr;
	int SubSize = 0;
	CSVFileGroup CSVFileList;

	Folder();
	Folder(string FileDir);
	string FolderName();
	bool DirExist(string dir);
	void Push(string dir);
	void CreateNewFolder(string filename, bool Override = false, bool Debug = false);
	void CreateNewCSVFile(string filename, string Header = "");
	void ImportNewCSVFile(string filename, bool pasted = false);
	void ImportNewCSVFile(CSVFile file, string filename);
	Folder* GetSubFolderAt(int x);
	Folder* GetSubFolder(string dir);
	Folder* FindFolder(string filename);
	void RemoveFolder(string filename);
	int del(const char* csDeleteFolderPath_i);
	void Delete();

	void PrintAllSubFolder();
	void PrintAllCSVFile();

	void CreateProfile(string Username = "", string Password = "", string ID = "", string Fullname = "", string DOB = "", string Class = "", string Courses = "");
	void RemoveProfile(string Username = "",string ID = "", string Fullname = "");
	void CreateCourse(string ID = "");
	void RemoveCourse(string ID = "");
};

#endif