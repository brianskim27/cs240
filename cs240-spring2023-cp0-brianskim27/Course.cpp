#include <iostream>
#include <stdlib.h>
#include "Course.h"
#include "Roster.h"

using namespace std;

Course::Course(string name, string section, unsigned int capacity, string instruct) {
	courseName = name;
	courseSection = section;
	maximumCapacity = capacity;
	instructor = instruct;
}

Course::Course() {
	courseName = "";
	courseSection = "";
	maximumCapacity = 0;
	instructor = "";
	Roster roster;
}

void Course::show() {
	cout << courseName << courseSection << " (" << maximumCapacity << "): " << instructor << endl;
}
