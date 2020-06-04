#ifndef _Utilities_H_
#define _Utilities_H_

#include <iostream>
#include <windows.h>
#include <filesystem>
#include <string>
#include <string.h>
#include <iomanip>
#include <direct.h>
#define GetCurrentDir _getcwd
#include "CSVFile.h"

using namespace std;

void PrintCSVFile(CSVFile& file);
string IntToString(int x);
int StringToInt(string S);
bool ValidCharacter(char C);
string CurrentDir();
string CurrentPath();

template <typename T>
class Node {
public:
	T data;
	Node *Next = nullptr;
	Node *Prev = nullptr;
	Node(){}
	Node(T &data);
};

template <typename T>
class LinkedList {
private:

public:
	Node<T>* Head = nullptr;
	Node<T>* Tail = nullptr;
	int Size = 0;
	void Push(T &data);
	void Pop(Node<T>*& PopedPointer);
	void Pop(int id);
	Node<T>* GetAt(int id);
	void Delete();
};

#endif