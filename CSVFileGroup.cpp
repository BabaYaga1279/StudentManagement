#include "CSVFileGroup.h"

CSVFileGroup::CSVFileGroup(){}

CSVFileGroup::CSVFileGroup(string NameList, string FileDir) {
	FileReader filereader(FileDir);

	this->NameList = NameList;
	filereader.Read(NameList, FileNameList);
	for (int i = 0; i < FileNameList.x; ++i) {
		CSVFile Course;
		string S = FileNameList.data[i][0];
		if (!IsCSVFile(S)) continue;
		filereader.Read(FileNameList.data[i][0], Course);
		FileList.Push(Course);
	}
}

CSVFileGroup::CSVFileGroup(string NameList, FileReader& filereader) {
	this->NameList = NameList;
	filereader.Read(NameList, FileNameList);
	for (int i = 0; i < FileNameList.x; ++i) {
		CSVFile Course;
		string S = FileNameList.data[i][0];
		if (!IsCSVFile(S)) continue;
		filereader.Read(FileNameList.data[i][0], Course);
		FileList.Push(Course);
	}
}

bool CSVFileGroup::IsCSVFile(string filename) {
	if (filename.length() > 4) {
		int l = filename.length();
		string S = "";
		S = filename.substr(l - 4, 4);
		if (S == ".csv") return true;
	}
	return false;
}

void CSVFileGroup::PrintFileNameList() {
	PrintCSVFile(FileNameList);
}

void CSVFileGroup::PrintOneFile(string filename) {
	int x, y;
	if (!FileNameList.Find(filename, x, y)) {
		cout << filename << " Not found" << endl;
		return;
	}

	CSVFile Tmp = FileList.GetAt(x) != nullptr ? FileList.GetAt(x)->data : CSVFile();

	PrintCSVFile(Tmp);
}

void CSVFileGroup::ImportNewFile(string filename, string FileDir) {
	FileReader filereader(FileDir);

	if (FileNameList.Find(filename)) DeleteFile(filename);
	CSVFile NewFile;
	filereader.Read(filename, NewFile);
	FileList.Push(NewFile);
	FileNameList.AddRow(filename);
}

void CSVFileGroup::ImportNewFile(string filename, FileReader& filereader) {
	if (FileNameList.Find(filename)) DeleteFile(filename);
	CSVFile NewFile;
	filereader.Read(filename, NewFile);
	FileList.Push(NewFile);
	FileNameList.AddRow(filename);
}

void CSVFileGroup::CreateNewFile(string filename, bool Override, string Header) {
	int x, y;
	if (FileNameList.Find(filename, x, y)) {
		if (!Override) {
			cout << filename << " Already exist !" << endl;
			return;
		}
		DeleteFile(x);
	}
	FileNameList.AddRow(filename);

	CSVFile Tmp;
	string S = Header;	// Header of file ("No,Name,ID...")
	if (S == "") {
		auto xtf = FileList.GetAt(0);
		if (xtf == nullptr) {
			cout << "Enter first row of your csv file, each block is seperated by ',' : \n";
			getline(cin, S);
		}
		else {
			Tmp = xtf->data;
			for (int j = 0; j < Tmp.y - 1; ++j) S = S + Tmp.data[0][j] + ',';
			if (Tmp.y > 0) S = S + Tmp.data[0][Tmp.y - 1];
		}
	}
	
	 
	CSVFile NewFile = CSVFile(S);
	FileList.Push(NewFile);
}

void CSVFileGroup::AddRowToFile(string filename, string Row, bool Check, int row, int col) {
	if (filename.find(".csv") == string::npos) filename += ".csv";

	if (!Check && !FileNameList.Find(filename, row, col)) {
		cout << "Can not add row !" << endl;
		return;
	}
	FileList.GetAt(row)->data.AddRow(Row);
}

void CSVFileGroup::CreateNewRowInFile(string filename) {
	int row, col;
	if (!FileNameList.Find(filename, row, col)) {
		cout << filename << " not exist !" << endl;
		return;
	}

	CSVFile Tmp = FileList.GetAt(row)->data;

	string NewRow = "";
	string word = "";
	for (int j = 0; j < Tmp.y; ++j) {
		if (Tmp.data[0][j] == "No") {
			word = IntToString(Tmp.x);
		}
		else
		{
			cout << "Input " << Tmp.data[0][j] << " :\n";
			getline(cin ,word);
		}
		NewRow = NewRow + word + ',';
	}
	if (NewRow[NewRow.length() - 1] == ',') NewRow.erase(NewRow.length() - 1, 1);
	NewRow = NewRow + '\n';

	AddRowToFile(filename, NewRow, true, row, col);
}

void CSVFileGroup::DeleteFile(int row) {
	if (row >= FileNameList.x) {
		cout << "Can't delete File" << endl;
		return;
	}
	FileList.GetAt(row)->data.Delete();
	FileList.Pop(row);
	FileNameList.RemoveRow(row);
}

void CSVFileGroup::DeleteFile(string S) {
	int row, col;
	if (!FileNameList.Find(S, row, col)) {
		cout << "Can't delete File " << S << endl;
		return;
	}
	DeleteFile(row);
}

void CSVFileGroup::DeleteRowInFile(string filename, int row, bool Check, int x, int y) {
	if (row == 0) return;
	if (!Check && !FileNameList.Find(filename, x, y)) {
		cout << "Can't find " << filename << endl;
		return;
	}
	CSVFile Tmp = FileList.GetAt(x)->data;
	if (row >= Tmp.x) {
		cout << "Can't delete Row " << row << endl;
		return;
	}

	FileList.GetAt(x)->data.RemoveRow(row);
}

void CSVFileGroup::DeleteRowInFile(string filename, string RowName) {
	int x, y;
	if (!FileNameList.Find(filename, x, y)) {
		cout << "Can't find " << filename << endl;
		return;
	}
	int row, col;
	CSVFile Tmp = FileList.GetAt(x)->data;
	if (!Tmp.Find(RowName, row, col)) {
		cout << RowName << " doesn't exist" << endl;
		return;
	}
	DeleteRowInFile(filename, row, true, x, y);
}

void CSVFileGroup::Delete(string FileDir) {
	FileReader filereader(FileDir);

	filereader.Write(NameList, FileNameList);
	for (int i = 0; i < FileNameList.x; ++i) filereader.Write(FileNameList.data[i][0], FileList.GetAt(i)->data);
	for (int i = 0; i < FileNameList.x; ++i) FileList.GetAt(i)->data.Delete();
	FileNameList.Delete();
	FileList.Delete();
}

void CSVFileGroup::Delete(FileReader &filereader) {
	filereader.Write(NameList, FileNameList);
	for (int i = 0; i < FileNameList.x; ++i) filereader.Write(FileNameList.data[i][0], FileList.GetAt(i)->data);
	for (int i = 0; i < FileNameList.x; ++i) FileList.GetAt(i)->data.Delete();
	FileNameList.Delete();
	FileList.Delete();
}

CSVFile* CSVFileGroup::Find(string filename) {
	if (filename == "") return nullptr;

	int x, y;
	if (FileNameList.Find(filename, x, y)) {
		auto t = FileList.GetAt(x);
		if (t != nullptr) return &(t->data);
	}

	return nullptr;
}