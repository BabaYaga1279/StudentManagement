#include "student.h"


int main()
{
    cout << "You have logged in as an student" << endl;
    int choice;
    while (true)
    {
        cout << "1.Check in" << endl << "2.View check in result" << endl << "3.view schedules" << endl << "4.view score in course" << endl << "5.Log out" << endl;
        cout << "Your choice: " << endl;
        cin >> choice;
        if (choice == 5)
        {
            break;
        }
    }
    return 0;
}
