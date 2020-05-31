#include <iostream>
#include "FileReader.h"
#include "Utilities.h"

using namespace std;

void FileReader::ScoutFile(string filename, int& row, int& col) {
	file.open(filename, ios::in);
	string firstline = "", tmp;
	row = 0;
	col = 0;

	if (!file.good()) {
		file.close();
		file.open(filename, ios::out);
		file.close();
		return;
	}

	getline(file, firstline);
	tmp = firstline;
	while (tmp != "" && !file.eof()) {
		++row;
		getline(file, tmp);
	}
	for (int i = 0; i < firstline.length(); ++i) if (firstline[i] == ',') ++col;
	if (firstline.length() > 0) ++col;
	file.close();
}

void FileReader::Read(string filename, CSVFile& data) {
	int row, col;
	ScoutFile(filename, row, col);
	data.Delete();
	data = CSVFile(row, col);
	file.open(filename, ios::in);
	string tmp = "";
	int x = 0, y = 0;

	if (!file.good()) {
		file.close();
		file.open(filename, ios::out);
		file.close();
		return;
	}

	getline(file, tmp);
	for (int i = 0; i < tmp.length(); ++i) if (!ValidCharacter(tmp[i])) {
		tmp.erase(i, 1); 
		--i;
	}
	while (tmp != "" && !file.eof()) {
		string word = "";
		for (int i = 0; i < tmp.length(); ++i) if (tmp[i] != ',') word += tmp[i];
		else {
			data.data[x][y] = word;
			word = "";
			++y;
			if (y >= data.y) break;
		}
		if (y < data.y) data.data[x][y] = word;
		++x;
		y = 0;
		getline(file, tmp);
	}
	file.close();
}
void FileReader::Write(string filename, CSVFile& data) {
	file.open(filename, ios::out);
	string tmp = "";
	for (int i = 0; i < data.x; ++i) {
		for (int j = 0; j < data.y - 1; ++j) tmp += data.data[i][j] + ',';
		if (data.y > 0) tmp += data.data[i][data.y - 1];
		file << tmp << '\n';
		tmp = "";
	}
	file.close();
}