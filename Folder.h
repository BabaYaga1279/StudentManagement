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
	bool DirExist(string dir);
	void Push(string dir);
	void CreateNewFolder(string filename, bool Override = false);
	Folder* GetSubFolderAt(int x);
	Folder* GetSubFolder(string dir);
	void RemoveFolder(string filename);
	int del(const char* csDeleteFolderPath_i);
	void Delete();

	void PrintAllSubFolder();
	void PrintAllCSVFile();
};

#endif