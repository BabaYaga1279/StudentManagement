#include "student.h"
void adjust(string A, string B[])
{
    int j=0;
    for (int i=0; i<18; ++i) B[i]="";
    for (int i=0; i<A.length(); ++i)
    {
        if (A[i] == ',')
        {
            ++j;
        }
        else
        {
            B[j]+=A[i];
        }
    }
}

void viewschedule (string nameoffile)
{
    string A, B[17];
    ifstream f (nameoffile);
    getline (f,A);
    while (!f.eof())
    {
        getline (f,A);
        adjust(A,B);
        cout << "No: " << B[0] << endl;
        cout << "Course ID: " << B[1] << endl;
        cout << "Course name: " << B[2] << endl;
        cout << "Class: " << B[3] << endl;
        cout << "Lecturer username: " << B[4] << endl;
        cout << "Lecturer name: " << B[5] << endl;
        cout << "Lecturer degree: " << B[6] << endl;
        cout << "Lecturer gender: " << B[7] << endl;
        cout << "Start date: " << B[8] << endl;
        cout << "end date: " << B[9] << endl;
        cout << "Date of week: " << B[10] << endl;
        cout << "start hour: " << B[11] << endl;
        cout << "Start minute: " << B[12] << endl;
        cout << "end hour: " << B[13] << endl;
        cout << "end minute: " << B[14] << endl;
        cout << "Room: " << B[15] << endl;
        cout << endl;
    }
}
