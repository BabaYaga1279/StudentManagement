#ifndef _Utilities_H_
#define _Utilities_H_

#include <string>
#include <string.h>
#include "CSVFile.h"

using namespace std;

void PrintFileCSV(CSVFile& file);
string IntToString(int x);
int StringToInt(string S);
bool ValidCharacter(char C);

template <typename T>
class Node {
public:
	T data;
	Node *Next = nullptr;
	Node *Prev = nullptr;
	Node(){}
	Node(T data) {
		this->data = data;
	}
};

template <typename T>
class LinkedList {
private:

public:
	Node<T>* Head = nullptr;
	Node<T>* Tail = nullptr;
	int Size = 0;

	void Push(T data);
	void Pop(Node<T>*& PopedPointer);
	void Pop(int id);
	Node<T>* GetAt(int id);
	void Delete();
};

#endif