#include "lecturer.h"
int main()
{
    cout << "You have logged in as a lecturer" << endl;
    int choice;
    while (true)
    {
        cout << "1.view list of courses in a semester" << endl << "2.view list of students in a course" << endl << "3.view attendance list of a course" << endl << "4.edit an attendance" << endl << "5.import scoreboard of a course" << endl << "6.edit grade of a student" << endl << "7.view a scoreboard" << endl << "8.log out" << endl;
        cout << "Your choice: " << endl;
        cin >> choice;
        if (choice == 8)
        {
            break;
        }
    }
    return 0;
}
