#include <stdlib.h>
#include <iostream>
using namespace std;

class Course {
	public:
		string crn;
		string department;
		string number;
		string name;
		string* studentArr;
		int numStudents;
		int max_numStudents;
		
		Course();
		~Course();
		void reallocateStudent(int newSize);
};
