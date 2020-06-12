#ifndef _CSVFileGroup_H_
#define _CSVFileGroup_H_

#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include "FileReader.h"
#include "CSVFile.h"


class CSVFileGroup {
public:
	string NameList = "";
	int width[30] = { 4,4,4,4,4 };
	CSVFile FileNameList;
	LinkedList<CSVFile> FileList;

	CSVFileGroup();
	CSVFileGroup(string NameList, string FileDir = "");	// filereader
	CSVFileGroup(string NameList, FileReader& filereader);

	bool IsCSVFile(string filename);
	void PrintFileNameList();
	void PrintOneFile(string filename);
	void ImportNewFile(string filename, string FileDir = "");	// filereader
	void ImportNewFile(string filename, FileReader& filereader);
	void CreateNewFile(string filename, bool Override = false, string Header = "");
	void AddRowToFile(string filename, string Row, bool Check = false, int row = -1, int col = -1);
	void CreateNewRowInFile(string filename);
	void DeleteFile(int row);
	void DeleteFile(string S);
	void DeleteRowInFile(string filename, int row, bool Check = false, int x = -1, int y = -1);
	void DeleteRowInFile(string filename, string RowName);
	void Delete(string FileDir = "");	// filereader
	void Delete(FileReader& filereader);

	CSVFile* Find(string filename = "");
};

#endif