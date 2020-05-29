#include "lecturer.h"
string nameoffile;
int main()
{
    cout << "You have logged in as a lecturer" << endl;
    int choice;
    while (true)
    {
        cout << "1.view list of courses in a semester" << endl << "2.view list of students in a course" << endl << "3.view attendance list of a course" << endl << "4.edit an attendance" << endl << "5.import scoreboard of a course" << endl << "6.edit grade of a student" << endl << "7.view a scoreboard" << endl << "8.log out" << endl;
        cout << "Your choice: " << endl;
        cin >> choice;
        if (choice == 2)
        {
            cout << "Please enter a file u want to " << endl;
            cin.ignore();
            getline(cin,nameoffile);
            viewstudenofcourse(nameoffile);
        }
        if (choice==7)
        {
            cout << "Please enter the file containing the score: " << endl;
            cin.ignore();
            getline (cin,nameoffile);
            viewscore(nameoffile);
        }
        if (choice == 8)
        {
            break;
        }
    }
    return 0;
}
