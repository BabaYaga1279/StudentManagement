#include <iostream>

#include <iomanip>

#include "FileReader.h"
#include "Utilities.h"
#include "CSVFile.h"
#include "ClassUtilities.h"
#include "ScheduleUtilities.h"

using namespace std;

int main() {
	
	ClassUtilities ClassManager;

	ClassManager.PrintClass("19APCS1-Student.csv");

	ClassManager.ImportNewClass("19APCS2-Student.csv");

	ClassManager.PrintClass("19APCS2-Student.csv");

	ClassManager.PrintClassList();
	
	ScheduleUtilities ScheduleManager;

	ScheduleManager.PrintScheduleNameList();

	ScheduleManager.PrintSchedule("19APCS1-Schedule.csv");

	//ScheduleManager.DeleteCourse("19APCS1-Schedule.csv", "IT6969");

	//ScheduleManager.PrintSchedule("19APCS1-Schedule.csv");

	//ScheduleManager.CreateCourse("19APCS1-Schedule.csv", "2", "IT6969", "Trailer to Programming", "", "JohnySin", "Johny Sin", "Premium", "Male", "31/12/2019", "31/12/2020", "SUN", "6", "59", "18", "59", "I99");

	//ScheduleManager.PrintSchedule("19APCS1-Schedule.csv");

	return 0;
}