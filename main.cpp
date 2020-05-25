#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

class CSVFile {
public:
	string** data;
	int x = 0, y = 0;
	CSVFile() {}
	CSVFile(int x, int y) {
		this->x = x;
		this->y = y;
		data = new string * [x];
		for (int i = 0; i < x; ++i) data[i] = new string[y];
	}
	void Delete() {
		for (int i = 0; i < x; ++i) delete[] data[i];
		if (x > 0) delete[] data;
		x = 0; y = 0;
	}
	void AddRow(string line) {
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
		if (j < Tmpy) Tmp[Tmpx - 1][j] = word;

		Delete();
		data = Tmp;
		x = Tmpx;
		y = Tmpy;
	}
	void EditRow(int row, string line) {
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
	void EditBlock(int x, int y, string S) {
		if (x >= this->x) return;
		if (y >= this->y) return;
		data[x][y] = S;
	}
	void RemoveRow(int row) {
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
		data = Tmp;
		x = Tmpx;
		y = Tmpy;
	}
	void SwapRow(int row1, int row2) {
		string* T = data[row1];
		data[row1] = data[row2];
		data[row2] = T;
	}
	void Sort(int col, int rowl, int rowr) {
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
	void Reverse() {
		for (int i = 0; i < x / 2; ++i) SwapRow(i, x - i - 1);
	}
	void SortByColume(int col, bool accending) {
		Sort(col, 0, x - 1);
		if (!accending) Reverse();
	}
};

class FileReader {
private:
	fstream file;
	void ScoutFile(string filename, int &row, int& col) {
		file.open(filename, ios::in);
		string firstline = "", tmp;
		row = 0;
		col = 0;
		getline(file, firstline);
		tmp = firstline;
		while (tmp != "") {
			++row;
			getline(file, tmp);
		}
		for (int i = 0; i < firstline.length(); ++i) if (firstline[i] == ',') ++col;
		if (firstline.length() > 0) ++col;
		file.close();
}

public:
	void Read(string filename,CSVFile & data) {
		int row, col;
		ScoutFile(filename, row, col);
		data.Delete();
		data = CSVFile(row, col);
		file.open(filename, ios::in);
		string tmp = "";
		int x = 0, y = 0;
		getline(file, tmp);
		while (tmp != "") {
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
	void Write(string filename, CSVFile& data) {
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
};

void PrintFileCSV(CSVFile &file) {
	for (int i = 0; i < file.x; ++i) {
		for (int j = 0; j < file.y; ++j) cout << file.data[i][j] << ' ';
		cout << '\n';
	}
}

int main() {
	FileReader filereader;

	CSVFile lecturer;
	filereader.Read("accounts_lecturer.csv", lecturer);

	//lecturer.AddRow("teacher1,teacher1\n");
	//lecturer.SwapRow(2, 3);
	lecturer.SortByColume(0, false);
	lecturer.EditBlock(3, 1, "teacher0");
	PrintFileCSV(lecturer);

	filereader.Write("accounts_lecturer.csv", lecturer);
	lecturer.Delete();
	return 0;
}