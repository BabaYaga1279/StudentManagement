#include <iostream>
#include "Utilities.h"

using namespace std;

void PrintFileCSV(CSVFile& file) {
	for (int i = 0; i < file.x; ++i) {
		for (int j = 0; j < file.y; ++j) cout << file.data[i][j] << ' ';
		cout << '\n';
	}
}