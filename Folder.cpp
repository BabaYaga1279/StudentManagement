#include "Folder.h"

Folder::Folder(){}

Folder::Folder(string FileDir) {
	this->FileDir = FileDir;
	filereader = FileReader(FileDir);

	filereader.Read("FolderList.csv", file_name_list);

	csv_list = CSVFileGroup("CSVFileList.csv", filereader);

}

bool Folder::DirExist(string dir) {
	DWORD ftyp = GetFileAttributesA(dir.c_str());

	if (ftyp == INVALID_FILE_ATTRIBUTES) return false;
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY) return true;
	
	return false;
}

void Folder::ImportNewCSVFile(string filename, string FileDir) {
	filereader.ChangeDir(FileDir);

	csv_list.ImportNewFile(filename, filereader);
}

void Folder::CreateNewFolder(string filename, bool Override) {
	string dir = filename;

	if (dir.find(FileDir) == string::npos) dir = FileDir + dir;

	if (CreateDirectory(dir.c_str(), NULL)) {
		cerr << dir << " created !" << endl;
	}
	else if (ERROR_ALREADY_EXISTS == GetLastError()) {
		cerr << dir << " aready exits !" << endl;
		if (Override) RemoveFolder(filename);
		if (file_name_list.Find(filename)) return;
	}
	else {
		cerr << "Can't create folder" << endl;
		return;
	}

	file_name_list.AddRow(filename);
}

void Folder::RemoveFolder(string filename) {
	string dir = filename;

	if (dir.find(FileDir) == string::npos) dir = FileDir + dir;

	if (RemoveDirectory(dir.c_str())) {
		cerr << dir << " deleted !" << endl;
	}
	else {
		cerr << "Can't delete folder" << endl;
		return;
	}

	int x, y;
	if (file_name_list.Find(filename, x, y)) file_name_list.RemoveRow(x);
}

void Folder::Delete() {
	filereader.ChangeDir(FileDir);

	filereader.Write("FolderList.csv", file_name_list);
	file_name_list.Delete();

	csv_list.Delete(filereader);
} 

