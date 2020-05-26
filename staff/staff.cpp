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


