#include "staff.h"
student *phead=nullptr;
string nameoffile, ID;

int main()
{
    cout << "You have logged in as an academic staff" << endl;
    int choice;
    while (true)
    {
        cout << "1.Class" << endl << "2.Course" << endl << "3.Scoreboard" << endl << "4.Attendance lists" << endl << "5.Log out" << endl;
        cout << "Your choice: " << endl;
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter the file you want to adjust: " << endl;
            cin.ignore();
            getline (cin,nameoffile);
            importstudentofaclass(nameoffile,phead);
            while (true)
            {
                cout << "1.Add a student to a class" << endl << "2.Edit an existing student" << endl << "3.Remove a student" << endl << "4.Change student class" << endl << "5.View class list" << endl << "6.View student list of a class" <<endl << "7.Back to menu" << endl;
                cout << "Your choice: " << endl;
                cin >> choice;
                if (choice==1)
                {
                    addstudenttoclass(nameoffile,phead);
                }
                if (choice==2)
                {
                    editstudent(nameoffile,phead);
                }
                if (choice == 7)
                {
                    deleteall(phead);
                    break;
                }
            }
        }
        if (choice ==2)
        {
            while(true)
            {
                cout << "1.Adjust academic years and semesters" << endl << "2.Import courses" << endl << "3.Add a course" << endl << "4.Edit a course" << endl << "5.Remove a course" << endl << "6.Remove a student from a course" << endl
                << "7.Add a student to a course" << endl << "8.View courses in a semester" << endl << "9.View student list in a course" << endl << "10.View attendance list of a course" << endl << "11.Adjust lecturers" << endl << "12.Back to menu" << endl;
                cout << "Your choice: ";
                cin >> choice;
                break;
            }
        }
        if (choice ==3 )
        {
            while (true)
            {
                cout << "1.View a scoreboard of a course" << endl << "2.export a scoreboard" << endl << "3.Back to menu" << endl;
                cout << "Your choice: " <<endl;
                cin >> choice;
                break;
            }
        }
        if (choice ==4)
        {
            while (true)
            {
                cout << "1.Search and view attendance of a course" << endl << "2.Export an attendance list to a csv file" << endl << "3.Back to menu" << endl;
                break;
            }
        }
        if (choice == 5)
        {
           break;
        }
    }
    return 0;
}


