#include "UI.h"

void Login(Folder& file, Folder*& profile) {
    string user, pass;
    profile = nullptr;

    auto t = file.FindFolder("Accounts");
    while (true) {
        system("cls");
        cout << "Enter user name (or 0 to exit) : \n";
        cin >> user;

        if (user == "0") return;

        auto t2 = t->FindFolder(user);
        CSVFile pf;

        if (t2 == nullptr) {
            cout << user << " not found!\n";
            _getch();
            continue;
        }
        else {
            auto tmp = t2->CSVFileList.FileList.GetAt(0);
            if (tmp == nullptr) {
                cout << "file is error!\n";
                _getch();
                return;
            }
            pf = tmp->data;
        }

        cout << "Enter password : \n";
        cin >> pass;

        if (pass == pf.data[1][1]) {
            cout << "Logged in!\n";
            profile = t2;
            _getch();
            return;
        }
        else {
            cout << "Wrong password ! Try again \n";
            _getch();
        }
    }
}
void EditProfile(Folder& file, Folder*& profile) {
    while (true) {
        auto t = profile->CSVFileList.FileList.GetAt(0);

        for (int i = 0; i < t->data.y; ++i) cout << i << ")" << t->data.data[1][i] << endl;
        int choice = 0;
        string Data;
        cout << "Enter number you want to edit :\n";
        cin >> choice;
        cout << "Enter context you wish it to be :\n";
        cin >> Data;

        auto Classes = file.FindFolder("Classes");
        Classes = Classes->FindFolder(t->data.data[1][5]);
        auto t2 = Classes->CSVFileList.FileList.GetAt(0);

        t->data.data[1][choice] = Data;

        if (choice < 2) {
            cout << "Finished\n";
            _getch();
            return;
        }

        int x, y;
        t2->data.Find(t->data.data[1][2], x, y);
        if (choice - 1 < t2->data.y) t2->data.data[x][choice - 1] = Data;

        cout << "Finished\n";
        _getch();
        return;
    }
}

void Staff_ImportAClass(Folder& file) {
    auto Classes = file.FindFolder("Classes");
    string Name = "";

    while (true) {
        cout << "Enter class name (or 0 to exit) : \n";
        cin >> Name;

        if (Name == "0") return;

        cout << "Please paste " << Name << "-Student.csv to the folder containing StudentManagement.exe to import the file .\n";
        cout << "Press Enter to continue when you have pasted the file, Esc to start again or 0 to exit .\n";
        char key = _getch();
        if (key == 27) continue;
        if (key == '0') return;

        Classes->CreateNewFolder(Name, true);
        Classes = Classes->FindFolder(Name);
        Classes->ImportNewCSVFile(Name + "-Student.csv", true);
        auto t = Classes->CSVFileList.FileList.GetAt(0);
        if (t == nullptr) {
            cout << "File error!\n";
            _getch();
            return;
        }
        CSVFile students = t->data;

        auto Accounts = file.FindFolder("Accounts");
        Accounts->CreateNewFolder(Name, true);
        Accounts = Accounts->FindFolder(Name);

        for (int i = 1; i < students.x; ++i) Accounts->CreateProfile("", "", students.data[i][1], students.data[i][2], students.data[i][3], students.data[i][4]);

        cout << "Import finished! Press any key to go back to main menu\n";
        _getch();
        break;
    }
}
void Staff_AddStudentToClass(Folder& file) {
    string ClassName = "";
    auto Classes = file.FindFolder("Classes");
    while (true) {
        cout << "Enter class name (or 0 to exit) : \n";
        cin >> ClassName;

        if (ClassName == "0") return;

        Classes = Classes->FindFolder(ClassName);
        if (Classes == nullptr) {
            cout << "Class not found !\n";
            _getch();
            return;
        }

        string ID, FullName, DOB;

        cout << "Enter Student ID: \n";
        cin >> ID;
        cout << "Enter Student full name: \n";
        cin.ignore();
        getline(cin, FullName);
        cout << "Enter Student date of birth (dd/mm/yyy): \n";
        cin >> DOB;

        auto t = Classes->CSVFileList.FileList.GetAt(0);
        if (t == nullptr) {
            cout << "File error!\n";
            _getch();
            return;
        }

        string No = IntToString(StringToInt(t->data.data[t->data.x - 1][0]) + 1);

        t->data.AddRow(No + ',' + ID + ',' + FullName + ',' + DOB + ',' + ClassName + '\n');

        auto Accounts = file.FindFolder("Accounts");
        Accounts = Accounts->FindFolder(ClassName);

        Accounts->CreateProfile("", "", ID, FullName, DOB, ClassName);

        cout << "Add new student finished! Press any key to go back to main menu\n";
        _getch();
        break;
    }
}
void Staff_EditStudent(Folder& file) {
    while (true) {
        string Class, ID, Data;
        cout << "Enter name of class of student you want to edit !\n";
        cin >> Class;
        cout << "Enter that student ID !\n";
        cin >> ID;

        auto Classes = file.FindFolder("Classes");
        Classes = Classes->FindFolder(Class);
        auto t = Classes->CSVFileList.FileList.GetAt(0);
        int x, y;
        t->data.Find(ID, x, y);

        for (int i = 1; i < t->data.y; ++i) cout << i << ")" << t->data.data[x][i] << endl;

        auto Accounts = file.FindFolder("Accounts");
        Accounts = Accounts->FindFolder(Class);
        Accounts = Accounts->FindFolder(ID);
        auto t2 = Accounts->CSVFileList.FileList.GetAt(0);

        int choice = 0;
        cout << "Enter number you want to edit :\n";
        cin >> choice;
        cout << "Enter context you wish it to be :\n";
        cin >> Data;
        t->data.data[x][choice] = Data;
        t2->data.data[1][choice + 1] = Data;
        if (choice == 1) t2->data.data[1][0] = Data;
        if (choice == 3) t2->data.data[1][1] = Data;

        cout << "Edit Finished ! Press any key\n";
        _getch();
        return;
    }
}
void Staff_RemoveStudent(Folder& file) {
    while (true) {
        string Class, ID;
        cout << "Enter name of class of student you want to remove !\n";
        cin >> Class;
        cout << "Enter that student ID !\n";
        cin >> ID;

        auto Classes = file.FindFolder("Classes");
        Classes = Classes->FindFolder(Class);
        auto t = Classes->CSVFileList.FileList.GetAt(0);
        int x, y;
        t->data.Find(ID, x, y);

        t->data.RemoveRow(x);

        auto Accounts = file.FindFolder("Accounts");
        Accounts = Accounts->FindFolder(Class);
        Accounts->RemoveProfile(ID);

        cout << "Remove finished ! Press any key\n";
        _getch();
        return;
    }
}
void Staff_ChangeStudentClass(Folder& file) {
    while (true) {
        string Class1, Class2, ID;
        cout << "Enter name of old class of student !\n";
        cin >> Class1;
        cout << "Enter name of new class of student !\n";
        cin >> Class2;
        cout << "Enter that student ID !\n";
        cin >> ID;

        auto Classes = file.FindFolder("Classes");
        Classes = Classes->FindFolder(Class1);
        auto t = Classes->CSVFileList.FileList.GetAt(0);
        int x, y;
        t->data.Find(ID, x, y);
        string row = "";
        for (int i = 0; i < y - 1; ++i) row += t->data.data[x][i] + ',';
        row += t->data.data[x][y];
        string FN, DOB;
        FN = t->data.data[x][2];
        DOB = t->data.data[x][3];
        t->data.RemoveRow(x);

        Classes = file.FindFolder("Classes");
        Classes = Classes->FindFolder(Class2);
        t = Classes->CSVFileList.FileList.GetAt(0);
        t->data.AddRow(row);

        auto Accounts = file.FindFolder("Accounts");
        Accounts = Accounts->FindFolder(Class1);
        Accounts->RemoveProfile(ID);

        Accounts = file.FindFolder("Accounts");
        Accounts = Accounts->FindFolder(Class2);
        Accounts->CreateProfile("", "", ID, FN, DOB, Class2);

        cout << "Swap finished ! Press any key\n";
        _getch();
        return;
    }
}
void Staff_PrintClassList(Folder& file) {
    auto t = file.FindFolder("Classes");
    PrintCSVFile(t->FolderNameList);
}
void Staff_PrintStudentList(Folder& file) {
    string Name;
    cout << "Enter class name you want to print\n";
    cin >> Name;
    auto t = file.FindFolder("Classes");
    t = t->FindFolder(Name);
    if (t == nullptr) {
        cout << "Class not found\n";
        _getch();
        return;
    }

    auto t2 = t->CSVFileList.FileList.GetAt(0);
    if (t2 == nullptr) {
        cout << "file error\n";
        _getch();
        return;
    }

    PrintCSVFile(t2->data);
}
void Staff_CreateAcademicYear(Folder& file) {
}
void Staff_CreateSemester(Folder& file) {
}
void Staff_ViewYearsAndSemester(Folder& file) {
}
void Staff_ImportCourse(Folder& file) {
}
void Staff_AddNewCourse(Folder& file) {
}
void Staff_EditCourse(Folder& file) {
}
void Staff_RemoveCourse(Folder& file) {
}
void Staff_RemoveStudentFromCourse(Folder& file) {
}
void Staff_AddStudentToCourse(Folder& file) {
}
void Staff_PrintCourse(Folder& file) {
}
void Staff_PrintCourseStudent(Folder& file) {
}
void Staff_PrintCourseAttendance(Folder& file) {
}
void Staff_PrintLecturer(Folder& file) {
}
void Staff_CreateLecturer(Folder& file) {
}
void Staff_EditLecturer(Folder& file) {
}
void Staff_RemoveLecturer(Folder& file) {
}
void Staff_PrintScoreBoard(Folder& file) {
}
void Staff(Folder& file, Folder*& profile) {

    int choice;
    while (true)
    {
        system("cls");
        cout << "You have logged in as an academic staff" << endl;
        cout << "0.Profile" << endl << "1.Class" << endl << "2.Course" << endl << "3.Scoreboard" << endl << "4.Attendance lists" << endl << "5.Log out" << endl;
        cout << "Your choice: " << endl;
        cin >> choice;
        if (choice == 0) {
            cout << "1.Print Profile" << endl << "2.Edit Profile" << endl << "3.Back to menu" << endl;
            cout << "Your choice: " << endl;
            cin >> choice;
            switch (choice)
            {
            case 1:
                PrintCSVFile(profile->CSVFileList.FileList.GetAt(0)->data);
                _getch();
                break;
            case 2:
                EditProfile(file, profile);
                break;
            case 3:
                break;
            default:
                break;
            }
            continue;
        }
        if (choice == 1)
        {
            while (true)
            {
                cout << "1.Import a class" << endl << "2.Add student to a class" << endl
                    << "3.Edit student" << endl
                    << "4.Remove a student" << endl << "5.Change student class" << endl
                    << "6.View class list" << endl << "7.View student list of a class" << endl
                    << "8.Back to menu" << endl;
                cout << "Your choice: " << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    Staff_ImportAClass(file);
                    break;
                case 2:
                    Staff_AddStudentToClass(file);
                    break;
                case 3:
                    Staff_EditStudent(file);
                    break;
                case 4:
                    Staff_RemoveStudent(file);
                    break;
                case 5:
                    Staff_ChangeStudentClass(file);
                    break;
                case 6:
                    Staff_PrintClassList(file);
                    break;
                case 7:
                    Staff_PrintStudentList(file);
                    break;
                case 8:
                    break;
                default:
                    break;
                }
                if (choice == 8) break;
            }
            continue;
        }
        if (choice == 2)
        {
            while (true)
            {
                cout << "1.Adjust academic years and semesters" << endl << "2.Import courses" << endl
                    << "3.Add a course" << endl << "4.Edit a course" << endl
                    << "5.Remove a course" << endl << "6.Remove a student from a course" << endl
                    << "7.Add a student to a course" << endl << "8.View courses in a semester" << endl
                    << "9.View student list in a course" << endl << "10.View attendance list of a course" << endl
                    << "11.Adjust lecturers" << endl << "12.Back to menu" << endl;
                cout << "Your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    break;
                case 10:
                    break;
                case 11:
                    break;
                default:
                    break;
                }

                if (choice == 12) break;
            }
            continue;
        }
        if (choice == 3)
        {
            while (true)
            {
                cout << "1.View a scoreboard of a course" << endl << "2.export a scoreboard" << endl << "3.Back to menu" << endl;
                cout << "Your choice: " << endl;
                cin >> choice;
                break;
            }
            continue;
        }
        if (choice == 4)
        {
            while (true)
            {
                cout << "1.Search and view attendance of a course" << endl << "2.Export an attendance list to a csv file" << endl << "3.Back to menu" << endl;
                break;
            }
            continue;
        }
        if (choice == 5)
        {
            break;
        }
    }
}

void Student_CheckIn(Folder& file) {

}
void Student_Schedule(Folder& file) {

}
void Student_Score(Folder& file) {

}
void Student(Folder& file, Folder*& profile) {
    int choice;
    while (true)
    {
        system("cls");
        cout << "You have logged in as an student" << endl;
        cout << "1.Check in" << endl << "2.View check in result" << endl << "3.view schedules" << endl << "4.view score in course" << endl << "5.Log out" << endl;
        cout << "Your choice: " << endl;
        cin >> choice;
        if (choice == 3)
        {
            cout << "enter the file of schedule: " << endl;
        }
        if (choice == 4)
        {
            cout << "Please enter the file contain your score: " << endl;

            cout << "Please enter your ID: " << endl;

        }
        if (choice == 5)
        {
            break;
        }
    }
}

void Lecturer_Course(Folder& file) {

}
void Lecturer_CourseStudent(Folder& file) {

}
void Lecturer_CourseAttending(Folder& file) {

}
void Lecturer_EditCourseAttending(Folder& file) {

}
void Lecturer_ImportScore(Folder& file) {

}
void Lecturer_EditScore(Folder& file) {

}
void Lecturer_PrintScore(Folder& file) {

}
void Lecturer(Folder& file, Folder*& profile) {
    
    int choice;
    while (true)
    {
        system("cls");
        cout << "You have logged in as a lecturer" << endl;
        cout << "1.view list of courses in a semester" << endl << "2.view list of students in a course" << endl << "3.view attendance list of a course" << endl << "4.edit an attendance" << endl << "5.import scoreboard of a course" << endl << "6.edit grade of a student" << endl << "7.view a scoreboard" << endl << "8.log out" << endl;
        cout << "Your choice: " << endl;
        cin >> choice;
        if (choice == 2)
        {
            cout << "Please enter a file u want to " << endl;
            cin.ignore();

        }
        if (choice == 7)
        {
            cout << "Please enter the file containing the score: " << endl;
            cin.ignore();
        }
        if (choice == 8)
        {
            break;
        }
    }
}