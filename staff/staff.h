#ifndef STAFF_H_
#define STAFF_H_
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>;
using namespace std;

struct student
{
    string no;
    string id;
    string fullname;
    string dob;
    string Class;
    student *pnext=nullptr;
};

void adjust(string A, string B[]);
void importstudentofaclass(string nameoffile,student *&phead);
void addstudenttoclass (string A, student *phead);
void editstudent(string nameoffile, student *phead);
void deleteall (student *&phead);
void removestudent (student *&phead, string nameoffile, string ID);
void changeclass (string nameoffile, student *&phead);
void viewclasslist ();
void viewstudentofclass (student *phead);


#endif // STAFF_H_
