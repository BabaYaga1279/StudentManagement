#include <iostream>

#include <iomanip>

#include "FileReader.h"
#include "Utilities.h"
#include "ClassUtilities.h"

using namespace std;


int main() {
	ClassUtilities ClassManager;

	ClassManager.PrintClass("19APCS1-Student.csv");

	ClassManager.ImportNewClass("19APCS2-Student.csv");

	ClassManager.PrintClass("19APCS2-Student.csv");

	ClassManager.PrintClassList();

	FileReader fr;

	CSVFile Tfile;

	fr.Read("19APCS1-Student.csv", Tfile);

	cout<<Tfile.data[0][0];

	return 0;
}