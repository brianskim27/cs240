#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include "course.h"
using namespace std;

Course::Course() {
	numStudents = 0;
	studentArr = new string[0];
	max_numStudents = 1;
}

Course::~Course() {
	if(studentArr != nullptr) {
		delete[] studentArr;
	}
}

void Course::reallocateStudent(int newSize) {
	string* newArr = new string[newSize];
	for(int i = 0; i < numStudents; i++) {
		newArr[i] = studentArr[i];
	}
	delete[] studentArr;
	studentArr = newArr;
	max_numStudents = newSize;
}
