#include "student.h"
string nameoffile, ID;

int main()
{
    cout << "You have logged in as an student" << endl;
    int choice;
    while (true)
    {
        cout << "1.Check in" << endl << "2.View check in result" << endl << "3.view schedules" << endl << "4.view score in course" << endl << "5.Log out" << endl;
        cout << "Your choice: " << endl;
        cin >> choice;
        if (choice==3)
        {
            cout << "enter the file of schedule: " << endl;
            cin.ignore();
            getline (cin,nameoffile);
            viewschedule(nameoffile);
        }
        if (choice == 4)
        {
            cout << "Please enter the file contain your score: " << endl;
            cin.ignore();
            getline(cin,nameoffile);
            cout << "Please enter your ID: " << endl;
            getline (cin,ID);
            viewscore(nameoffile,ID);
        }
        if (choice == 5)
        {
            break;
        }
    }
    return 0;
}
