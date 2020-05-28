#include <iostream>
#include "Utilities.h"

using namespace std;

void PrintFileCSV(CSVFile& file) {
	for (int i = 0; i < file.x; ++i) {
		for (int j = 0; j < file.y; ++j) cout << file.data[i][j] << ' ';
		cout << '\n';
	}
}

string IntToString(int x) {
	string T = "";
	if (x < 0) {
		T = "-";
		x *= -1;
	}
	string S = "";
	while (x) {
		S = (char)(x % 10 + 48) + S;
		x /= 10;
	}
	return T + S;
}

int StringToInt(string S) {
	int x = 0;
	for (int i = 0; i < S.length(); ++i) x = x * 10 + S[i] - 48;
	return x;
}

template <typename T>
void LinkedList<T>::Push(T data) {
	++Size;
	Node<T>* NewPointer = new Node<T>(data);
	if (Head == nullptr) {
		Head = NewPointer;
		Tail = NewPointer;
		return;
	}
	Tail->Next = NewPointer;
	NewPointer->Prev = Tail;
	Tail = NewPointer;
}

template <typename T>
void LinkedList<T>::Pop(Node<T>*& PopedPointer) {
	if (PopedPointer == nullptr) return;
	--Size;
	if (PopedPointer == Tail) Tail = Tail->Prev;
	if (PopedPointer == Head) Head = Head->Next;
	Node<T>* PrevPointer = PopedPointer->Prev;
	Node<T>* NextPointer = PopedPointer->Next;
	if (PrevPointer != nullptr) PrevPointer->Next = NextPointer;
	if (NextPointer != nullptr) NextPointer->Prev = PrevPointer;
	delete PopedPointer;
	PopedPointer = nullptr;
}

template <typename T>
Node<T>* LinkedList<T>::GetAt(int id) {
	int count = 0;
	for (auto i = Head; i != nullptr; i = i->Next) {
		if (count == id) return i;
		++count;
	}
	return nullptr;
}

template <typename T>
void LinkedList<T>::Delete() {
	if (Head == nullptr) return;
	Size = 0;
	for (auto i = Head->Next; i != nullptr; i = i->Next) {
		delete Head;
		Head = nullptr;
		Head = i;
	}
	delete Head;
	Head = nullptr;
	Tail = nullptr;
}

void TempoaryFunction() {
	LinkedList<CSVFile> TempObj;
	CSVFile TempData;
	TempObj.Push(TempData);
	auto t = TempObj.GetAt(0);
	TempObj.Pop(t);
	TempObj.Delete();
}