#include <iostream>
#include <stdlib.h>
using namespace std;

class Student {
	public:
		string bnumber;
		string userId;
		string firstName;
		string lastName;
		string* courseArr;
		int numCourses;
		int max_numCourses;

		Student();
		~Student();
		void reallocateCourse(int newSize);
		void removeCourse(string crn);
		void addCourse(string crn);
};

	

