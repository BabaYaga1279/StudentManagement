#include "lecturer.h"
void adjust(string A, string B[])
{
    int j=0;
    for (int i=0; i<7; ++i) B[i]="";
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

void viewstudenofcourse (string nameoffile)
{
    string A,B[6];
    ifstream f (nameoffile);
    getline (f,A);
    while (!f.eof())
    {
        getline(f,A);
        adjust(A,B);
        cout << "No: " << B[0] << endl;
        cout << "ID: " << B[1] << endl;
        cout << "Full name: " << B[2] << endl;
        cout << "Dob: " << B[3] << endl;
        cout << "Class: " << B[4] <<endl;
        cout << endl;
    }
}

void viewscore (string nameoffile)
{
    string A, B[7];
    ifstream f (nameoffile);
    getline(f,A);
    while (!f.eof())
    {
        getline (f,A);
        adjust(A,B);
        cout << "No: " << B[0] << endl;
        cout << "ID: " << B[1] << endl;
        cout << "Full name: " << B[2] << endl;
        cout << "Mid term: " << B[3] << endl;
        cout << "Final: " << B[4] << endl;
        cout << "Bonus: " << B[5] << endl;
        cout << "Total: " << B[6] << endl;
        cout << endl;
    }
}
