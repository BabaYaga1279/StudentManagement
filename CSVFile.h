#ifndef _CSVFile_H_
#define _CSVFile_H_

#include <string>
#include <string.h>
#include <fstream>

using namespace std;

class CSVFile {
public:
	string** data;
	int x = 0, y = 0;
	CSVFile();
	CSVFile(int x, int y);
	CSVFile(string S);
	void Delete();
	void AddRow(string line);
	void EditRow(int row, string line);
	void EditBlock(int x, int y, string S);
	void RemoveRow(int row);
	void SwapRow(int row1, int row2);
	void Sort(int col, int rowl, int rowr);
	void Reverse();
	void SortByColume(int col, bool accending);
	bool Find(string S);
	bool Find(string S, int& x, int& y);
};

#endif