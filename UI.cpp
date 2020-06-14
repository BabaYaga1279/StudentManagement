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
        
        for (int i = 0; i < t->data.y; ++i) cout << i << "_"<< t->data.data[0][i] <<" ) " << t->data.data[1][i] << endl;
        int choice = 0;
        string Data;
        cout << "Enter number you want to edit :\n";
        cin >> choice;
        cout << "Enter context you wish it to be :\n";
        cin >> Data;

        t->data.data[1][choice] = Data;

        cout << "Finished\n";
        cout << "Press  Esc to keep editing or any key to exit .\n";
        char key = _getch();
        if (key == 27) continue;
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
    auto t = file.FindFolder("Courses");
    cout << "Avalable academic year : \n";
    PrintCSVFile(t->FolderNameList);
    cout << "\n";
    cout << "Input Academic year you want to create: \n";
    string year;
    cin >> year;
    t->CreateNewFolder(year);
    cout << year << " created !\n";
    _getch();
}
void Staff_CreateSemester(Folder& file) {
    auto t = file.FindFolder("Courses");
    cout << "Input year you want to create semester\n";
    string year;
    cin >> year;
    t = t->FindFolder(year);
    if (t == nullptr) {
        cout << year << " not found\n";
        return;
    }
    PrintCSVFile(t->FolderNameList);
    cout << "Input semester you want to create";
    string SEM;
    cin >> SEM;
    t->CreateNewFolder(SEM);
    cout << SEM << " created !\n";
    _getch();
}
void Staff_ViewYearsAndSemester(Folder& file) {
    auto t = file.FindFolder("Courses");
    t->PrintAllSubFolder();
}
void Staff_ImportCourse(Folder& file) {
    auto t = file.FindFolder("Courses");
    string Year, Sem, Course, Class;

    while (true) {
        cout << "Enter academic year of course : \n";
        cin >> Year;
        t = t->FindFolder(Year);
        if (t == nullptr) {
            cout << "File error\n";
            return;
        }
        cout << "Enter semester of the year: \n";
        cin >> Sem;
        t = t->FindFolder(Sem);
        if (t == nullptr) {
            cout << "File error\n";
            return;
        }

        FileReader filereader;
        CSVFile Tmp;

        string filename;
        cout << "Enter filename :\n";
        cin >> filename;
        cout << "Please paste " << filename << " to the folder containing StudentManagement.exe, press any key when finish \n";
        _getch();
        filereader.Read(filename, Tmp);
        Class = Tmp.data[1][3];
        t = t->FindFolder(Class);
        if (t == nullptr) {
            cout << "File error\n";
            return;
        }
        Course = Tmp.data[1][2];

        string No, ID, LecU, Startd, Endd, DOW, Starthm, Endhm, Room;
        ID = Tmp.Get(1, 1);
        LecU = Tmp.Get(1,4);
        Startd = Tmp.Get(1, 5);
        Endd = Tmp.Get(1, 6);
        DOW = Tmp.Get(1, 7);
        Starthm = Tmp.Get(1, 8);
        Endhm = Tmp.Get(1, 9);
        Room = Tmp.Get(1, 10);


        auto tt = t->CSVFileList.FileList.GetAt(0);
        No = IntToString(StringToInt(Tmp.Get(Tmp.x - 1, 0)) + 1);
        string Data = No + "," + ID + "," + Course + "," + Class + "," + LecU + "," + Startd + "," + Endd + "," + DOW + "," + Starthm + "," + Endhm + "," + Room + '\n';

        cout << "New course is : \n";
        cout << Data;

        cout << "Press Enter to continue when you have pasted the file, Esc to start again or 0 to exit .\n";
        char key = _getch();
        if (key == 27) continue;
        if (key == '0') return;

        tt->data.AddRow(Data);

        t->CreateNewFolder(ID);
        auto t2 = t->FindFolder(ID);

        auto t3 = file.FindFolder("Classes");
        t3 = t3->FindFolder(Class);
        auto tt3 = t3->CSVFileList.FileList.GetAt(0);

        t2->ImportNewCSVFile(tt3->data, t3->CSVFileList.FileNameList.Get(0, 0));

        cout << "Import finished! Press any key to go back to main menu\n";
        _getch();
        break;
    }
}
void Staff_AddNewCourse(Folder& file) {
    auto t = file.FindFolder("Courses");
    string Year, Sem, Course, Class;

    while (true) {
        cout << "Enter academic year of course : \n";
        cin >> Year;
        t = t->FindFolder(Year);
        if (t == nullptr) {
            cout << "File error\n";
            return;
        }
        cout << "Enter semester of the year: \n";
        cin >> Sem;
        t = t->FindFolder(Sem);
        if (t == nullptr) {
            cout << "File error\n";
            return;
        }
        cout << "Enter class:\n";
        cin >> Class;
        t = t->FindFolder(Class);
        if (t == nullptr) {
            cout << "File error\n";
            return;
        }
        cout << "Enter course name: \n";
        cin >> Course;

        string No, ID, LecU, Startd, Endd, DOW, Starthm, Endhm, Room;
        cout << "Input course ID:\n";
        cin >> ID;
        cout << "Input lecturer username\n:";
        cin >> LecU;
        cout << "Input start date:\n";
        cin >> Startd;
        cout << "Input end date:\n";
        cin >> Endd;
        cout << "Input day of week:\n";
        cin >> DOW;
        cout << "Input start hour:min :\n";
        cin >> Starthm;
        cout << "Input end hour:min :\n";
        cin >> Endhm;
        cout << "Input room:\n";
        cin >> Room;

        auto tt = t->CSVFileList.FileList.GetAt(0);
        No = IntToString(StringToInt(tt->data.data[0][tt->data.y - 1]) + 1);
        string Data = No + "," + ID + "," + Course + "," + Class + "," + LecU + "," + Startd + "," + Endd + "," + DOW + "," + Starthm + "," + Endhm + "," + Room + '\n';

        cout << "New course is : \n";
        cout << Data;

        cout << "Press Enter to continue when you have pasted the file, Esc to start again or 0 to exit .\n";
        char key = _getch();
        if (key == 27) continue;
        if (key == '0') return;

        tt->data.AddRow(Data);

        t->CreateNewFolder(ID);
        auto t2 = t->FindFolder(ID);

        auto t3 = file.FindFolder("Classes");
        t3 = t3->FindFolder(Class);
        auto tt3 = t3->CSVFileList.FileList.GetAt(0);

        t2->ImportNewCSVFile(tt3->data, t3->CSVFileList.FileNameList.Get(0, 0));

        cout << "Import finished! Press any key to go back to main menu\n";
        _getch();
        break;
    }
}
void Staff_EditCourse(Folder& file) {
    string Year, Sem, Class;
    cout << "Input year\n";
    cin >> Year;
    cout << "Input Semester\n";
    cin >> Sem;
    cout << "Input Class\n";
    cin >> Class;
    auto t = file.FindFolder("Courses");
    t = t->FindFolder(Year);
    if (t == nullptr) return;
    t = t->FindFolder(Sem);
    if (t == nullptr) return;
    t = t->FindFolder(Class);
    if (t == nullptr) return;
    auto tt = t->CSVFileList.FileList.GetAt(0);
    if (tt == nullptr) return;
    int x, y;
    for (int i = 1; i < tt->data.x; ++i) {
        cout << i << ") " << tt->data.Get(i, 1) << '\n';
    }
    cout << "Enter number you want to edit :\n";
    cin >> x;
    for (int j = 0; j < tt->data.y; ++j) {
        cout << j << ") " << tt->data.Get(x, j) << '\n';
    }
    cout << "Enter number you want to edit :\n";
    cin >> y;
    string Data;
    cout << tt->data.Get(x, y) << '\n';
    cout << "Enter what you want to edit:\n";
    cin.ignore();
    getline(cin, Data);

    if (tt->data.Get(x, y) != "") tt->data.data[x][y] = Data;

    cout << "Edit completed !\n";

    for (int j = 0; j < y; ++j) cout << tt->data.Get(x, j) << ' ';
    cout << endl;
    _getch();
}
void Staff_RemoveCourse(Folder& file) {
    string Year, Sem, Class;
    cout << "Input year\n";
    cin >> Year;
    cout << "Input Semester\n";
    cin >> Sem;
    cout << "Input Class\n";
    cin >> Class;
    auto t = file.FindFolder("Courses");
    t = t->FindFolder(Year);
    if (t == nullptr) return;
    t = t->FindFolder(Sem);
    if (t == nullptr) return;
    t = t->FindFolder(Class);
    if (t == nullptr) return;
    auto tt = t->CSVFileList.FileList.GetAt(0);
    if (tt == nullptr) return;
    int x;
    for (int i = 1; i < tt->data.x; ++i) {
        cout << i << ") " << tt->data.Get(i, 1) << '\n';
    }
    cout << "Enter number you want to remove :\n";
    cin >> x;
    
    string ID = tt->data.Get(x, 1);

    tt->data.RemoveRow(x);
    t->RemoveFolder(ID);

    cout << "Remove finished! Press any key to go back to main menu\n";
    _getch();
}
void Staff_RemoveStudentFromCourse(Folder& file) {
    string Year, Sem, Class, Course, StudentID;
    cout << "Input year\n";
    cin >> Year;
    cout << "Input Semester\n";
    cin >> Sem;
    cout << "Input Class\n";
    cin >> Class;
    cout << "Input Course\n";
    cin >> Course;
    cout << "Input student id you want to remove\n";
    cin >> StudentID;

    auto t = file.FindFolder("Courses");
    if (t == nullptr) return;
    t = t->FindFolder(Year);
    if (t == nullptr) return;
    t = t->FindFolder(Sem);
    if (t == nullptr) return;
    t = t->FindFolder(Class);
    if (t == nullptr) return;
    t = t->FindFolder(Course);
    if (t == nullptr) return;

    auto tt = t->CSVFileList.Find(Class + "-Student.csv");
    if (tt == nullptr) return;

    int x, y;
    if (!tt->Find(StudentID, x, y)) {
        cout << StudentID << " doesn't exist\n";
        return;
    }

    tt->RemoveRow(x);
}
void Staff_AddStudentToCourse(Folder& file) {
    while (true) {
        string Year, Sem, Class, Course, StudentID, Name, DOB, No;
        cout << "Input year\n";
        cin >> Year;
        cout << "Input Semester\n";
        cin >> Sem;
        cout << "Input Class\n";
        cin >> Class;
        cout << "Input Course\n";
        cin >> Course;
        cout << "Input student id you want to add\n";
        cin >> StudentID;
        cout << "Input student fullname\n";
        cin >> Name;
        cout << "Input student date of birth\n";
        cin >> DOB;

        auto t = file.FindFolder("Courses");
        if (t == nullptr) return;
        t = t->FindFolder(Year);
        if (t == nullptr) return;
        t = t->FindFolder(Sem);
        if (t == nullptr) return;
        t = t->FindFolder(Class);
        if (t == nullptr) return;
        t = t->FindFolder(Course);
        if (t == nullptr) return;

        auto tt = t->CSVFileList.Find(Class + "-Student.csv");
        if (tt == nullptr) return;

        No = IntToString(StringToInt(tt->Get(tt->x - 1, 0)) + 1);
        string Data = No + ',' + StudentID + ',' + Name + ',' + DOB + '\n';

        cout << "New student is : \n";
        cout << Data;

        cout << "Press Enter to continue when you have pasted the file, Esc to start again or 0 to exit .\n";
        char key = _getch();
        if (key == 27) continue;
        if (key == '0') return;

        int x, y;
        if (tt->Find(StudentID, x, y)) {
            cout << StudentID << " already exist\n";
            return;
        }

        tt->AddRow(Data);
    } 
}
void Staff_PrintCourse(Folder& file) {
    auto t = file.FindFolder("Courses");
    t->PrintAllSubFolder();
}
void Staff_PrintCourseStudent(Folder& file) {
    string Year, Sem, Class, Course, StudentID;
    cout << "Input year\n";
    cin >> Year;
    cout << "Input Semester\n";
    cin >> Sem;
    cout << "Input Class\n";
    cin >> Class;
    cout << "Input Course\n";
    cin >> Course;
    auto t = file.FindFolder("Courses");
    if (t == nullptr) return;
    t = t->FindFolder(Year);
    if (t == nullptr) return;
    t = t->FindFolder(Sem);
    if (t == nullptr) return;
    t = t->FindFolder(Class);
    if (t == nullptr) return;
    t = t->FindFolder(Course);
    if (t == nullptr) return;
    PrintCSVFile(*t->CSVFileList.Find(Class + "-Student.csv"));
}
void Staff_PrintCourseAttendance(Folder& file) {
    string Year, Sem, Class, Course, StudentID;
    cout << "Input year\n";
    cin >> Year;
    cout << "Input Semester\n";
    cin >> Sem;
    cout << "Input Class\n";
    cin >> Class;
    cout << "Input Course\n";
    cin >> Course;
    auto t = file.FindFolder("Courses");
    if (t == nullptr) return;
    t = t->FindFolder(Year);
    if (t == nullptr) return;
    t = t->FindFolder(Sem);
    if (t == nullptr) return;
    t = t->FindFolder(Class);
    if (t == nullptr) return;
    t = t->FindFolder(Course);
    if (t == nullptr) return;
    PrintCSVFile(*t->CSVFileList.Find(Class + "-Student.csv"));
}
void Staff_ExportCourseAttendance(Folder& file) {
    string Year, Sem, Class, Course, StudentID;
    cout << "Input year\n";
    cin >> Year;
    cout << "Input Semester\n";
    cin >> Sem;
    cout << "Input Class\n";
    cin >> Class;
    cout << "Input Course\n";
    cin >> Course;
    auto t = file.FindFolder("Courses");
    if (t == nullptr) return;
    t = t->FindFolder(Year);
    if (t == nullptr) return;
    t = t->FindFolder(Sem);
    if (t == nullptr) return;
    t = t->FindFolder(Class);
    if (t == nullptr) return;
    t = t->FindFolder(Course);
    if (t == nullptr) return;
    FileReader filereader;

    filereader.Write(Class + "-Student.csv", *t->CSVFileList.Find(Class + "-Student.csv"));
}
void Staff_PrintLecturer(Folder& file) {
    auto t = file.FindFolder("Accounts");
    if (t == nullptr) return;
    t = t->FindFolder("Lecturers");
    if (t == nullptr) return;
    t->PrintAllSubFolder();
}
void Staff_CreateLecturer(Folder& file) {
    auto t = file.FindFolder("Accounts");
    t = t->FindFolder("Lecturers");
    t->CreateProfile("new", "new", "new", "new", "new", "new", "new");
    auto t2 = t->FindFolder("new_new_new");
    EditProfile(file, t2);
}
void Staff_EditLecturer(Folder& file) {
}
void Staff_RemoveLecturer(Folder& file) {
    auto t = file.FindFolder("Accounts");
    t = t->FindFolder("Lecturers");
    t->PrintAllSubFolder();
    cout << "Enter filename of lecturer you want to remove\n";
    string filename;
    cin.ignore();
    getline(cin, filename);
    
    t->RemoveFolder(filename);
}
void Staff_PrintScoreBoard(Folder& file) {
    string Year, Sem, Class, Course;
    cout << "Enter year\n";
    cin >> Year;
    cout << "Enter semester\n";
    cin >> Sem;
    cout << "Enter Class\n";
    cin >> Class;
    cout << "Enter Course\n";
    cin >> Course;

    auto t = file.FindFolder("Courses");
    if (t == nullptr) return;
    t = t->FindFolder(Year);
    if (t == nullptr) return;
    t = t->FindFolder(Sem);
    if (t == nullptr) return;
    t = t->FindFolder(Class);
    if (t == nullptr) return;
    t = t->FindFolder(Course);
    if (t == nullptr) return;

    PrintCSVFile(*t->CSVFileList.Find(Class + "-" + Course + "-Scoreboard.csv"));
}
void Staff_ExportScoreBoard(Folder& file) {
    string Year, Sem, Class, Course;
    cout << "Enter year\n";
    cin >> Year;
    cout << "Enter semester\n";
    cin >> Sem;
    cout << "Enter Class\n";
    cin >> Class;
    cout << "Enter Course\n";
    cin >> Course;

    auto t = file.FindFolder("Courses");
    if (t == nullptr) return;
    t = t->FindFolder(Year);
    if (t == nullptr) return;
    t = t->FindFolder(Sem);
    if (t == nullptr) return;
    t = t->FindFolder(Class);
    if (t == nullptr) return;
    t = t->FindFolder(Course);
    if (t == nullptr) return;

    FileReader filereader;

    filereader.Write(Class + "-" + Course + "-Scoreboard.csv",*t->CSVFileList.Find(Class + "-" + Course + "-Scoreboard.csv"));
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
                break;
            }
            _getch();
            continue;
        }
        if (choice == 2)
        {
            while (true)
            {
                cout << "1.Create academic year" << endl << "2.Create semester" << endl << "3.View years and semesters" << endl
                    << "4.Import courses" << endl << "5.Add a course" << endl << "6.Edit a course" << endl
                    << "7.Remove a course" << endl << "8.Remove a student from a course" << endl
                    << "9.Add a student to a course" << endl << "10.View courses in a semester" << endl
                    << "11.View student list in a course" << endl << "12.View attendance list of a course" << endl
                    << "13.Adjust lecturers" << endl << "14.Back to menu" << endl;
                cout << "Your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    Staff_CreateAcademicYear(file);
                    break;
                case 2:
                    Staff_CreateSemester(file);
                    break;
                case 3:
                    Staff_ViewYearsAndSemester(file);
                    break;
                case 4:
                    Staff_ImportCourse(file);
                    break;
                case 5:
                    Staff_AddNewCourse(file);
                    break;
                case 6:
                    Staff_EditCourse(file);
                    break;
                case 7:
                    Staff_RemoveCourse(file);
                    break;
                case 8:
                    Staff_RemoveStudentFromCourse(file);
                    break;
                case 9:
                    Staff_AddStudentToCourse(file);
                    break;
                case 10:
                    Staff_PrintCourse(file);
                    break;
                case 11:
                    Staff_PrintCourseStudent(file);
                    break;
                case 12:
                    Staff_PrintCourseAttendance(file);
                    break;
                case 13:
                    Staff_EditLecturer(file);
                    break;
                default:
                    break;
                }

                break;
            }
            _getch();
            continue;
        }
        if (choice == 3)
        {
            while (true)
            {
                cout << "1.View a scoreboard of a course" << endl << "2.export a scoreboard" << endl << "3.Back to menu" << endl;
                cout << "Your choice: " << endl;
                cin >> choice;
                switch (choice) {
                case 1:
                    Staff_PrintScoreBoard(file);
                    break;
                case 2:
                    Staff_ExportScoreBoard(file);
                    break;
                default:
                    break;
                }

                break;
            }
            _getch();
            continue;
        }
        if (choice == 4)
        {
            while (true)
            {
                cout << "1.Search and view attendance of a course" << endl << "2.Export an attendance list to a csv file" << endl << "3.Back to menu" << endl;
                cout << "Your choice: " << endl;
                cin >> choice;
                switch (choice) {
                case 1:
                    Staff_PrintCourseAttendance(file);
                    break;
                case 2:
                    Staff_ExportCourseAttendance(file);
                    break;
                default:
                    break;
                }
                break;
            }
            _getch();
            continue;
        }
        if (choice == 5)
        {
            break;
        }
    }
}

void Student_CheckIn(Folder& file, Folder*& profile) {
    string Course, Date;
    cout << "Input course to check in\n";
    cin >> Course;
    cout << "Input date \n";
    cin >> Date;
    profile->CreateNewFolder("CheckIn");
    auto t = profile->FindFolder("CheckIn");
    auto tt = t->CSVFileList.FileList.GetAt(0);
    if (tt == nullptr) {
        t->CreateNewCSVFile("CheckIn.csv", Course + ',' + Date + '\n');
        return;
    }

    tt->data.AddRow(Course + ',' + Date + '\n');
}
void Student_CheckInResult(Folder& file, Folder*& profile) {
    auto t = profile->FindFolder("CheckIn");
    if (t == nullptr) return;
    auto tt = t->CSVFileList.FileList.GetAt(0);
    if (tt == nullptr) return;

    PrintCSVFile(tt->data);
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
        if (choice == 1) {
            Student_CheckIn(file, profile);
        }
        if (choice == 2) {
            Student_CheckInResult(file, profile);

        }
        if (choice == 3)
        {
            Student_Schedule(file);
        }
        if (choice == 4)
        {
            Student_Score(file);

        }
        if (choice == 5)
        {
            break;
        }
    }
}

void Lecturer_PrintCourseList(Folder& file, Folder*& profile) {

}
void Lecturer_PrintCourseStudent(Folder& file, Folder*& profile) {

}
void Lecturer_PrintCourseAttending(Folder& file, Folder*& profile) {

}
void Lecturer_EditCourseAttending(Folder& file, Folder*& profile) {

}
void Lecturer_ImportCourseScore(Folder& file, Folder*& profile) {

}
void Lecturer_EditStudentScore(Folder& file, Folder*& profile) {

}
void Lecturer_PrintAllScore(Folder& file, Folder*& profile) {

}
void Lecturer(Folder& file, Folder*& profile) {
    
    int choice;
    while (true)
    {
        system("cls");
        cout << "You have logged in as a lecturer" << endl;
        cout << "1.view list of courses in a semester" << endl 
             << "2.view list of students in a course" << endl
             << "3.view attendance list of a course" << endl 
             << "4.edit an attendance" << endl 
             << "5.import scoreboard of a course" << endl 
             << "6.edit grade of a student" << endl 
             << "7.view a scoreboard" << endl 
             << "8.log out" << endl;
        cout << "Your choice: " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            Lecturer_PrintCourseList(file, profile);
            break;
        case 2:
            Lecturer_PrintCourseStudent(file, profile);
            break;
        case 3:
            Lecturer_PrintCourseAttending(file, profile);
            break;
        case 4:
            Lecturer_EditCourseAttending(file, profile);
            break;
        case 5:
            Lecturer_ImportCourseScore(file, profile);
            break;
        case 6:
            Lecturer_EditStudentScore(file, profile);
            break;
        case 7:
            Lecturer_PrintAllScore(file, profile);
            break;
        case 8:
            break;
        default:
            break;
        }
    }
}