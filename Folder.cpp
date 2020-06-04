#include "Folder.h"

Folder::Folder() {}

Folder::Folder(string FileDir) {
	cout << "Constructor " << FileDir << endl;
	this->FileDir = FileDir;
	FileReader filereader(FileDir);
	filereader.Read("FolderList.csv", FileNameList);
	for (int i = 0; i < FileNameList.x; ++i) {
		CreateNewFolder(FileNameList.data[i][0]);
		//Push(FileDir + FileNameList.data[i][0] + "/");
	}
	if (SubHead != nullptr) cout << "SuBhead " << SubHead->FileDir << endl;
}

bool Folder::DirExist(string dir) {
	DWORD ftyp = GetFileAttributesA(dir.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES) return false;
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY) return true;
	return false;
}

void Folder::Push(string dir) {
	cout << "Push " << dir << endl;
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

void Folder::CreateNewFolder(string filename, bool Override) {
	string dir = filename;
	if (dir.find(FileDir) == string::npos) dir = FileDir + dir;
	if (dir[dir.length() - 1] != '/') dir = dir + "/";
	if (CreateDirectory(dir.c_str(), NULL)) {
		cerr << dir << " created !" << endl;
	}
	else if (ERROR_ALREADY_EXISTS == GetLastError()) {
		cerr << dir << " aready exits !" << endl;
		if (Override) {
			RemoveFolder(filename);
			CreateNewFolder(filename);
			return;
		}
	}
	else {
		cerr << "Can't create folder" << endl;
		return;
	}

	int x, y;
	if (!FileNameList.Find(filename,x ,y)) FileNameList.AddRow(filename);

	if (GetSubFolderAt(x) == nullptr) Push(dir);
	
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
	if (FileNameList.Find(filename, x, y)) {
		Check = true;
		FileNameList.RemoveRow(x);
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
	cout << "Delete " << FileDir << endl;
	CreateDirectory(FileDir.c_str(), NULL);

	FileReader filereader(FileDir);
	for (int i = 0; i < FileNameList.x; ++i) {
		string S = FileNameList.data[i][0];
		if (S[S.length() - 1] == '/') FileNameList.data[i][0].erase(S.length() - 1, 1);
	}
	filereader.Write("FolderList.csv", FileNameList);
	FileNameList.Delete();

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
