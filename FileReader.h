#ifndef _FileReader_H_
#define _FileReader_H_

#include <fstream>
#include <string>
#include <string.h>
#include "CSVFile.h"

using namespace std;

class FileReader {
private:
	fstream file;
	string FileDir = "";
	void ScoutFile(string filename, int& row, int& col);

public:
	FileReader(string FileDir = "");
	void Read(string filename, CSVFile& data);
	void Write(string filename, CSVFile& data);
	void ChangeDir(string NewDir = "");
};

#endif