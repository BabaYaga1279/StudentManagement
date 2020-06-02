#include "CSVFile.h"

using namespace std;

CSVFile::CSVFile() {}

CSVFile::CSVFile(int x, int y) {
	this->x = x;
	this->y = y;
	if (x == 0) return;
	data = new string * [x];
	for (int i = 0; i < x; ++i) data[i] = new string[y];
}

CSVFile::CSVFile(string S) {
	if (S[S.length() - 1] != '\n') S += '\n';
	int row = 0, col = 0;
	for (int i = 0, commas = 0; i < S.length(); ++i) 
		if (S[i] == ',') ++commas;
		else if (S[i] == '\n') {
			++row;
			col = commas > col ? commas : col;
			commas = 0;
		}
	++col;
	

	this->x = row;
	this->y = col;
	if (x == 0) return;
	data = new string * [row];
	for (int i = 0; i < x; ++i) data[i] = new string[col];

	string word = "";
	int u = 0, v = 0;
	for (int i = 0; i < S.length(); ++i) {
		if (S[i] == ',') {
			data[u][v] = word;
			word = "";
			++v;
		} else
		if (S[i] == '\n') {
			data[u][v] = word;
			word = "";
			++u;
			v = 0;
		} else word = word + S[i];
	}
}

void CSVFile::Delete() {
	for (int i = 0; i < x; ++i) delete[] data[i];
	if (x > 0) delete[] data;
	x = 0; y = 0;
}

void CSVFile::AddRow(string line) {
	if (line[line.length() - 1] != '\n') line += '\n';
	string** Tmp;
	int Tmpx = x + 1, Tmpy = y;
	Tmp = new string * [Tmpx];
	for (int i = 0; i < x + 1; ++i) Tmp[i] = new string[Tmpy];
	for (int i = 0; i < x; ++i)
		for (int j = 0; j < y; ++j) Tmp[i][j] = data[i][j];
	string word = "";
	int j = 0;
	for (int i = 0; i < line.length(); ++i) if (line[i] != ',') word += line[i];
	else {
		Tmp[Tmpx - 1][j] = word;
		++j;
		word = "";
		if (j >= Tmpy) break;
	}
	if (j < Tmpy) {
		if (word[word.length() - 1] == '\n') word.erase(word.length() - 1, 1);
		Tmp[Tmpx - 1][j] = word;
	}
	Delete();
	data = Tmp;
	x = Tmpx;
	y = Tmpy;
}

void CSVFile::EditRow(int row, string line) {
	if (row >= x) return;
	int j = 0;
	string word = "";
	for (int i = 0; i < line.length(); ++i) if (line[i] != ',') word += line[i];
	else {
		data[row][j] = word;
		word = "";
		++j;
		if (j >= y) return;
	}
	if (j < y) data[row][j] = word;
}

void CSVFile::EditBlock(int x, int y, string S) {
	if (x >= this->x) return;
	if (y >= this->y) return;
	data[x][y] = S;
}

void CSVFile::RemoveRow(int row) {
	if (row >= x) return;
	string** Tmp;
	int Tmpx = x - 1, Tmpy = y;
	Tmp = new string * [Tmpx];
	for (int i = 0; i < Tmpx; ++i) Tmp[i] = new string[Tmpy];
	for (int i = 0; i < Tmpx; ++i) {
		int t = i;
		if (t >= row) ++t;
		for (int j = 0; j < Tmpy; ++j) Tmp[i][j] = data[t][j];
	}

	Delete();
	this->data = Tmp;
	this->x = Tmpx;
	this->y = Tmpy;
}

void CSVFile::SwapRow(int row1, int row2) {
	string* T = data[row1];
	data[row1] = data[row2];
	data[row2] = T;
}

void CSVFile::Sort(int col, int rowl, int rowr) {
	string M = data[(rowl + rowr) / 2][col];
	int rowi = rowl, rowj = rowr;
	while (rowi <= rowj) {
		while (data[rowi][col] < M) ++rowi;
		while (data[rowj][col] > M) --rowj;
		if (rowi <= rowj) {
			SwapRow(rowi, rowj);
			++rowi;
			--rowj;
		}
	}
	if (rowi < rowr) Sort(col, rowi, rowr);
	if (rowj > rowl) Sort(col, rowl, rowj);
}

void CSVFile::Reverse() {
	for (int i = 0; i < x / 2; ++i) SwapRow(i, x - i - 1);
}

void CSVFile::SortByColume(int col, bool accending) {
	Sort(col, 0, x - 1);
	if (!accending) Reverse();
}

bool CSVFile::Find(string S) {
	for (int i = 0; i < x; ++i)
		for (int j = 0; j < y; ++j) if (data[i][j] == S) return true;
	return false;
}

bool CSVFile::Find(string S, int& x, int& y) {
	for (int i = 0; i < this->x; ++i)
		for (int j = 0; j < this->y; ++j) if (data[i][j] == S || data[i][j] == S + '\n') {
			x = i;
			y = j;
			return true;
		}
	x = -1;
	y = -1;
	return false;
}

string CSVFile::Get(int x, int y) {
	if (x >= this->x || y >= this->y) return "";
	return data[x][y];
}