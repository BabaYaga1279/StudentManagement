#include "staff.h"


void importstudentofaclass(string nameoffile, student *&phead)
{
    student *cur;
    string B[6],A;
    ifstream f (nameoffile);
    getline (f,A);
    while (!f.eof())
    {
        getline(f,A);
        adjust (A,B);
        if (phead==nullptr)
        {
            phead= new student;
            phead->no=B[0];
            phead->id=B[1];
            phead->fullname=B[2];
            phead->dob=B[3];
            phead->Class=B[4];
            cur=phead;
        }
        else
        {
            cur->pnext=new student;
            cur->pnext->no=B[0];
            cur->pnext->id=B[1];
            cur->pnext->fullname=B[2];
            cur->pnext->dob=B[3];
            cur->pnext->Class=B[4];
            cur=cur->pnext;
        }
    }
    f.close();
}


void adjust(string A, string B[])
{
    int j=0;
    for (int i=0; i<6; ++i) B[i]="";
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

void deleteall (student *&phead)
{
    student *cur;
    while (phead != nullptr)
    {
        cur=phead;
        phead=phead->pnext;
        delete cur;
    }
}

void addstudenttoclass (string nameoffile, student *phead)
{
    while (phead->pnext != nullptr) phead=phead->pnext;
    phead->pnext=new student;
    string B[6],A;
    int i;
    ifstream f (nameoffile);
    while (!f.eof())
    {
        getline (f,A);
    }
    adjust(A,B);
    f.close();
    i=stoi(B[0])+1;
    B[0]=to_string(i);
    ofstream g ;
    g.open (nameoffile, ios_base::app);
    cout << "Please enter the ID, full name , dob of(dd/mm/yy) of the student: " << endl;
    phead->pnext->no=B[0];
    g << endl;
    g << B[0] << ",";
    cout << "ID:" << endl;
    cin.ignore();
    getline (cin,A);
    phead->pnext->id=A;
    g << A << ",";
    cout << "Full name: " << endl;
    getline (cin,A);
    phead->pnext->fullname=A;
    g << A << ",";
    cout << "Dob: " << endl;
    getline(cin,A);
    phead->pnext->dob=A;
    g << A << "," << B[4];
    phead->pnext->Class=B[4];
    g.close();
}
