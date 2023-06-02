#include <stdlib.h>
#include <iostream>

using namespace std;

class Course {
	public:
		Course(string, string, unsigned int, string);
		Course();
		void show();
	
	private:
		string courseName = "";
		string courseSection = "";
		unsigned int maximumCapacity = 0;
		string instructor = "";
};
