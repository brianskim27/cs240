#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include "student.h"
using namespace std;

Student::Student() {
        	numCourses = 0;
        	courseArr = nullptr;
        	max_numCourses = 1;
}

Student::~Student() {
	delete[] courseArr;
	courseArr = nullptr;
}
    
void Student::reallocateCourse(int newSize) {
	if(courseArr == nullptr) {
            	courseArr = new string[newSize];
            	max_numCourses = newSize;
		for(int i = 0; i < newSize; i++) {
			courseArr[i] = "";
		}
      	}	
        else {
            string *newArr = new string[newSize];
           	for (int i = 0; i < numCourses; i++) {
                	newArr[i] = courseArr[i];
            	}

	    	delete[] courseArr;
		courseArr = nullptr;
	    	courseArr = newArr;
            	max_numCourses = newSize;
        }
}

void Student::removeCourse(string crn) {
	int j = -1;
        for(int i = 0; i < numCourses; i++) {
            	if(courseArr[i] == crn) {
                	j = i;
                	break;
            	}
        }
        if(j != -1) {
            	for(int i = j; i < numCourses - 1; i++) {
                	courseArr[i] = courseArr[i + 1];
            	}
            	courseArr[numCourses - 1] = "";
            	numCourses--;
        }
}

void Student::addCourse(string crn) {
	if(numCourses >= max_numCourses) {
		reallocateCourse(max_numCourses *= 2);
	}
	else if(max_numCourses == 1) {
		reallocateCourse(2);
	}

	courseArr[numCourses] = crn;
	numCourses++;
}
