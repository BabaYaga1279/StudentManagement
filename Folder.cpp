#include "Folder.h"
#include <conio.h>

Folder::Folder() {}

Folder::Folder(string FileDir) {
	//cout << "Constructor " << FileDir << endl;
	this->FileDir = FileDir;
	FileReader filereader(FileDir);
	filereader.Read("FolderList.csv", FolderNameList);
	for (int i = 0; i < FolderNameList.x; ++i) {
		CreateNewFolder(FolderNameList.data[i][0]);
	}
	CSVFileList = CSVFileGroup("CSVFileList.csv", filereader);
}

string Folder::FolderName() {
	if (FileDir == "") return "";
	string foldername = "";
	for (int i = FileDir.length() - 2; i >= 0; --i) {
		if (FileDir[i] == '/') break;
		foldername = FileDir[i] + foldername;
	}
	return foldername;
}

bool Folder::DirExist(string dir) {
	DWORD ftyp = GetFileAttributesA(dir.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES) return false;
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY) return true;
	return false;
}

void Folder::Push(string dir) {
	//cout << "Push " << dir << endl;
	Folder* T = new Folder(dir);
	++SubSize;
	if (this->SubHead == nullptr) {
		this->SubHead = T;
		this->SubTail = T;
		return;
	}
	this->SubTail->Next = T;
	T->Prev = this->SubTail;
	this->SubTail = T;
}

void Folder::CreateNewFolder(string filename, bool Override, bool Debug) {
	string dir = filename;
	if (dir.find(FileDir) == string::npos) dir = FileDir + dir;
	if (dir[dir.length() - 1] != '/') dir = dir + "/";
	if (CreateDirectory(dir.c_str(), NULL)) {
		if (Debug) cerr << dir << " created !" << endl;
	}
	else if (ERROR_ALREADY_EXISTS == GetLastError()) {
		if (Debug) cerr << dir << " aready exits !" << endl;
		if (Override) {
			RemoveFolder(filename);
			CreateNewFolder(filename);
			return;
		}
	}
	else {
		if (Debug) cerr << "Can't create folder" << endl;
		return;
	}

	int x, y;
	if (!FolderNameList.Find(filename,x ,y)) FolderNameList.AddRow(filename);

	if (GetSubFolderAt(x) == nullptr) Push(dir);
	
}

void Folder::CreateNewCSVFile(string filename, string Header) {
	if (filename == "") return;
	if (filename.find(".csv") == string::npos) filename += ".csv";

	CSVFileList.CreateNewFile(filename, true, Header);
}

void Folder::ImportNewCSVFile(string filename, bool pasted) {
	if (filename == "") return;
	if (filename.find(".csv") == string::npos) filename += ".csv";

	if (!pasted) {
		cout << "Please patse "<<filename<<" into folder containing StudentManagement.exe\n";
		cout << "Press any key and enter after u did that . \n";
		_getch();
	}
	

	CSVFileList.ImportNewFile(filename, "");
}

void Folder::ImportNewCSVFile(CSVFile file, string filename) {
	if (filename.find(".csv") == string::npos) filename += ".csv";
	CSVFileList.ImportNewFile(file, filename);
}

Folder* Folder::GetSubFolderAt(int x) {
	int count = 0;
	for (auto t = SubHead; t != nullptr; t = t->Next) {
		if (count == x) return t;
		++count;
	}
	return nullptr;
}

Folder* Folder::GetSubFolder(string dir) {
	for (auto t = SubHead; t != nullptr; t = t->Next) {
		if (t->FileDir == dir) return t;
	}
	return nullptr;
}

void Folder::RemoveFolder(string filename) {
	bool Check = false;
	string dir = filename;
	if (dir.find(FileDir) == string::npos) dir = FileDir + dir;
	if (dir[dir.length() - 1] != '/') dir = dir + "/";
	int x, y;
	if (FolderNameList.Find(filename, x, y)) {
		Check = true;
		FolderNameList.RemoveRow(x);
		auto t = GetSubFolderAt(x);
		if (t != nullptr) {
			if (t == SubHead) SubHead = SubHead->Next;
			if (t == SubTail) SubTail = SubTail->Prev;
			t->Delete();
			delete t;
		}
	}
	if (RemoveDirectory(dir.c_str()) || del(dir.c_str()) == 0) {
		cerr << dir << " deleted !" << endl;
		Check = true;
	}
	else {
		
		cerr << "Can't delete folder" << endl;
	}
	SubSize -= Check;
}

Folder* Folder::FindFolder(string filename) {
	for (auto i = SubHead; i != nullptr; i = i->Next) {
		if (i->FileDir.find(filename) != string::npos) {
			return i;
		}
		auto t = i->FindFolder(filename);
		if (t != nullptr) return t;
	}

	return nullptr;
}

int Folder::del(const char* csDeleteFolderPath_i)
{
	int nFolderPathLen = strlen(csDeleteFolderPath_i);
	TCHAR* pszFrom = new TCHAR[nFolderPathLen + 2];
	strcpy(pszFrom, csDeleteFolderPath_i);
	pszFrom[nFolderPathLen] = 0;
	pszFrom[++nFolderPathLen] = 0;
	SHFILEOPSTRUCT stSHFileOpStruct = { 0 };
	stSHFileOpStruct.wFunc = FO_DELETE;
	stSHFileOpStruct.pFrom = pszFrom;
	stSHFileOpStruct.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR | FOF_SILENT;
	stSHFileOpStruct.fAnyOperationsAborted = FALSE;
	int nFileDeleteOprnRet = SHFileOperation(&stSHFileOpStruct);
	delete[]pszFrom;
	if (0 != nFileDeleteOprnRet)
	{
		return 1;
	}
	return 0;
}
void Folder::Delete() {
	//cout << "Delete " << FileDir << endl;
	CreateDirectory(FileDir.c_str(), NULL);
	FileReader filereader(FileDir);
	CSVFileList.Delete(filereader);
	for (int i = 0; i < FolderNameList.x; ++i) {
		string S = FolderNameList.data[i][0];
		if (S[S.length() - 1] == '/') FolderNameList.data[i][0].erase(S.length() - 1, 1);
	}
	filereader.Write("FolderList.csv", FolderNameList);
	FolderNameList.Delete();

	if (Prev != nullptr) Prev->Next = Next;
	if (Next != nullptr) Next->Prev = Prev;

	if (SubHead == nullptr) return;

	for (auto t = SubHead->Next; t != nullptr; t = t->Next) {
		SubHead->Delete();
		delete SubHead;
		SubHead = t;
	}

	SubHead->Delete();
	delete SubHead;

}

void Folder::PrintAllSubFolder() {
	cout << FileDir << endl;
	for (auto i = SubHead; i != nullptr; i = i->Next) i->PrintAllSubFolder();
}

void Folder::PrintAllCSVFile() {
	cout << "Printing all csv files \n";
	CSVFileList.PrintFileNameList();
}

void Folder::CreateProfile(string Username, string Password, string ID, string Fullname, string DOB, string Class, string Courses) {
	if (Username == "") Username = ID;
	if (Password == "") Password = DOB;
	
	string filename = ID + "_" + Fullname + '_' + Username;
	string Header = "Username,Password,ID,Fullname,Date of birth,Class,Courses\n";

	string Data = Username + ',' + Password + ',' + ID + ',' + Fullname + ',' + DOB + ',' + Class + ',' + Courses + '\n';
	CreateNewFolder(filename, true);

	auto t = FindFolder(filename);
	
	if (t == nullptr) {
		cout << "can't create profile";
		return;
	}

	t->CreateNewCSVFile(filename, Header);
	t->CSVFileList.AddRowToFile(filename, Data);
}

void Folder::RemoveProfile(string Username, string ID, string Fullname) {
	if (ID == "" && Fullname == "" && Username == "") return;
	auto t = ID != "" ? FindFolder(ID) : (Fullname != "" ? FindFolder(Fullname):FindFolder(Username) );
	RemoveFolder(t->FolderName());
}

void Folder::CreateCourse(string ID) {
	string filename = ID;
	string Header = "Course ID\n";
	string Data = ID + '\n';

	CreateNewFolder(filename, true);

	auto t = FindFolder(filename);

	if (t == nullptr) {
		cout << "can't create profile";
		return;
	}

	t->CreateNewCSVFile(filename, Header);
	t->CSVFileList.AddRowToFile(filename, Data);
}

void Folder::RemoveCourse(string ID) {
	if (ID == "") return;
	auto t = FindFolder(ID);
	RemoveFolder(t->FolderName());
}
