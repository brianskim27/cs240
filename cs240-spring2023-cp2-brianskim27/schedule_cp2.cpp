#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "course.h"
#include "student.h"
using namespace std;

bool valid_crn(const string& crn) {
	if(crn.length() != 6) {
		return false;
	}
	for(char c : crn) {
		if(!isdigit(c)) {
			return false;
		}
	}
	return true;
}

bool valid_department(const string& department) {
	if(department.length() < 2 || department.length() > 4) {
		return false;
	}
	for(char c : department) {
		if(!isupper(c)) {
			return false;
		}
	}
	return true;
}

bool valid_number(const string& number) {
	if(number.length() != 3) {
		return false;
	}
	int num = stoi(number);
	if(num < 100 || num > 700) {
		return false;
	}
	return true;
}

bool valid_bnumber(const string& bnumber) {
	if(bnumber.length() != 9) {
		return false;
	}
	if(bnumber.at(0) != 'B') {
		return false;
	}
	return true;
}

bool valid_userId(const string& userId) {
	if(!isalpha(userId.at(0))) {
		return false;
	}
	for(char c : userId) {
		if(!isdigit(c) && !isalpha(c)) { 
			return false;
		}
	}
	return true;	
}

int main() {
	cout << "Enter [\"build <crn> <department> <number> <name>\"" << endl << "       " << "\"cancel <crn>\"" << endl << "       " <<  "\"enroll <bnumber> <userid> <first> <last>\"" << endl << "       " << "\"add <bnumber> <crn>\"" << endl << "       " << "\"drop <bnumber> <crn>\"" << endl << "       " << "\"roster <crn>\"" << endl << "       " << "\"schedule <bnumber>\"" << endl << "       " << "\"quit\"]" << endl;
	
	const int MAX_COURSES = 1000;
	const int MAX_STUDENTS = 1000;
	int num_courses = 0;
	int num_students = 0;
	Course* courses = new Course[MAX_COURSES];
	Student* students = new Student[MAX_STUDENTS];
	
	while(true) {
		cout << ": ";
		string input;
		getline(cin, input);
		if(input.empty()) {
			cout << "Input Error: too few arguments" << endl;
			continue;
		}

		vector<string> args;
		string arg;
		for(char c : input) {
			if(isspace(c)) {
				args.push_back(arg);
				arg.clear();
			}
			else {
				arg += c;
			}
		}
		args.push_back(arg);	

		if(arg.empty()) {
			args.push_back(arg);
		}

		if(args[0] == "build") {
			if(args.size() < 5) {
				cout << "Input Error: too few arguments" << endl;
				continue;
			}

			string crn = args[1];
			string department = args[2];
			string number = args[3];
			string name;

			for(unsigned long i = 4; i < args.size(); i++) {
				name += args[i];
				if(i < args.size() - 1) {
					name += " ";
				}
			}

			if(!valid_crn(crn)) {
				cout << "Input Error: illegal CRN" << endl;
				continue;
			}
			else if(!valid_department(department)) {
				cout << "Input Error: illegal department" << endl;
				continue;
			}
			else if(!valid_number(number)) {
				cout << "Input Error: illegal course number" << endl;
				continue;
			}
			
			int x = 1;
			for(int i = 0; i < num_courses; i++) {
				if(courses[i].crn == crn) {
					x = 0;
					break;
				}
			}

			if(x == 0) {
				cout << "Fail: cannot build course " << department << number << " (CRN: " << crn << "): CRN exists" << endl;
			}
			else if(num_courses < MAX_COURSES) {
					courses[num_courses].crn = crn;
               	 			courses[num_courses].department = department;
                			courses[num_courses].number = number;
                			courses[num_courses].name = name;
               				courses[num_courses].numStudents = 0;
              				courses[num_courses].studentArr = nullptr;
					num_courses++;
					cout << "Success: built course " << department << number << " (CRN: " << crn << "): " << name << endl;
			}	
		}

		else if(args[0] == "cancel") {
			if(args.size() < 2) {
				cout << "Input Error: too few arguments" << endl;
				continue;
			}
			else if(args.size() > 2) {
				cout << "Warning: ignoring extra argument(s)" << endl;
				continue;
			}

			string crn = args[1];
			int x = 0;

			if(!valid_crn(crn)) {
				cout << "Input Error: illegal CRN" << endl;
				continue;
			}
			
			else if(num_courses < MAX_COURSES) {
				for(int i = 0; i < num_courses; i++) {
					if(courses[i].crn == crn) {
						for(int j = i; j < num_courses - 1; j++) {
							courses[j] = courses[j + 1];
						}
						x = 1;
						num_courses--;
						break;
					}
				}
			}
			
			if(x == 1) {
				cout << "Success: cancelled course " << crn << endl;
			}
			else if(x == 0) {
				cout << "Fail: cannot cancel course, CRN does not exist" << endl;
			}
		}

		else if(args[0] == "enroll") {
			if(args.size() < 5) {
				cout << "Input Error: too few arguments" << endl;
				continue;
			}
			else if(args.size() > 5) {
				cout << "Warning: ignoring extra argument(s)" << endl;
				continue;
			}

			string bnumber = args[1];
			string userId = args[2];
			string firstName = args[3];
			string lastName = args[4];

			if(!valid_bnumber(bnumber)) {
				cout << "Input Error: illegal B Number" << endl;
				continue;
			}
			else if(!valid_userId(userId)) {
				cout << "Input Error: illegal ID" << endl;
				continue;
			}
			
			int x = 1;	
			for(int i = 0; i < num_students; i++) {
			       if(students[i].bnumber == bnumber) {
				       x = 0;
				       break;
				}
			}
			if(x == 0) {
				cout << "Fail: cannot enroll student, B Number exists" << endl;
			}
			else if(num_students < MAX_STUDENTS) {
				students[num_students].bnumber = bnumber;
				students[num_students].userId = userId;
				students[num_students].firstName = firstName;
				students[num_students].lastName = lastName;
				students[num_students].numCourses = 0;
				students[num_students].courseArr = nullptr;
				num_students++;
				cout << "Success: enrolled student " << bnumber << " (" << userId << ") " << lastName << ", " << firstName << endl;
			}		
		}
		
		else if(args[0] == "add") {
			if(args.size() < 3) {
				cout << "Input Error: too few arguments" << endl;
				continue;
			}
			else if(args.size() > 3) {
				cout << "Warning: ignoring extra argument(s)" << endl;
				continue;
			}

			string bnumber = args[1];
			string crn = args[2];

			if(!valid_bnumber(bnumber)) {
				cout << "Input Error: illegal B Number" << endl;
				continue;
			}
			else if(!valid_crn(crn)) {
				cout << "Input Error: illegal CRN" << endl;
				continue;
			}
			
			int s_index = -1;
			for(int i = 0; i < num_students; i++) {
				if(students[i].bnumber == bnumber) {
					s_index = i;
					break;
				}
			}

			int c_index = -1;
			for(int i = 0; i < num_courses; i++) {
				if(courses[i].crn == crn) {
					c_index = i;
					break;
				}
			}

			int x = 1;
			for(int i = 0; i < students[s_index].numCourses; i++) {
				for(int j = 0; j < courses[c_index].numStudents; j++) {
					if(courses[c_index].studentArr[j] == bnumber) {
						x = 0;
						break;
					}
				}
			}

			if(courses[c_index].max_numStudents <= courses[c_index].numStudents) {
				courses[c_index].max_numStudents *= 2;
			}

			if(x == 0) {
				cout << "Fail: cannot add, student " << bnumber << " already enrolled in course " << courses[c_index].crn << endl;
				continue;
			}

			else if(courses[c_index].numStudents < courses[c_index].max_numStudents) {
				courses[c_index].numStudents++;
				int newSize = courses[c_index].numStudents;
				string* new_studentArr = new string[newSize];
						
				for(int i = 0; i < courses[c_index].numStudents - 1; i++) {
					new_studentArr[i] = courses[c_index].studentArr[i];
				}

				new_studentArr[newSize - 1] = bnumber;
				delete[] courses[c_index].studentArr;
				courses[c_index].studentArr = new_studentArr;
					
				students[s_index].reallocateCourse(newSize);
				students[s_index].courseArr[newSize - 1] = crn;

				cout << "Success: added student " << bnumber << " into course " << courses[c_index].crn << endl;

				students[s_index].addCourse(crn);
			}	
		}
		
		else if(args[0] == "drop") {
			if(args.size() < 3) {
				cout << "Input Error: too few arguments" << endl;
				continue;
			}
			else if(args.size() > 3) {
				cout << "Warning: Ignoring extra argument(s)" << endl;
				continue;
			}

			string bnumber = args[1];
			string crn = args[2];

			if(!valid_bnumber(bnumber)) {
				cout << "Input Error: invalid B Number" << endl;
				continue;
			}
			else if(!valid_crn(crn)) {
				cout << "Input Error: invalid CRN" << endl;
				continue;
			}
			
			int c_index = -1;
			for(int i = 0; i < num_courses; i++) {
				if(courses[i].crn == crn) {
					c_index = i;
					break;
				}
			}

			int s_index = -1;
			for(int j = 0; j < courses[c_index].numStudents; j++) {
				if(courses[c_index].studentArr[j] == bnumber) {
					s_index = j;
					break;
				}
			}

			courses[c_index].numStudents--;
			int newSize = courses[c_index].numStudents;
			string* new_studentArr = new string[newSize];
			int index = 0;
						
			for(int k = 0; k < courses[c_index].numStudents; k++) {
				if(k != s_index) {
					new_studentArr[index] = courses[c_index].studentArr[k];
					index++;
				}
			}

			delete[] courses[c_index].studentArr;
			courses[c_index].studentArr = new_studentArr;
					
			cout << "Success: removed student " << bnumber << " from course " << courses[c_index].crn << endl;
				
			for(int i = 0; i < num_students; i++) {
				if(students[i].bnumber == bnumber) {
					students[i].removeCourse(crn);
					break;
				}
			}
		}

		else if(args[0] == "roster") {
			if(args.size() < 2) {
				cout << "Input Error: too few arguments" << endl;
				continue;
			}
			if(args.size() > 2) {
				cout << "Warning: ignoring extra argument(s)" << endl;
				continue;
			}

			string crn = args[1];

			if(!valid_crn(crn)) {
				cout << "Input Error: illgal CRN" << endl;
				continue;
			}

			for(int i = 0; i < num_courses; i++) {
				if(courses[i].crn == crn) {
					cout << "CRN: " << courses[i].crn << endl;
					cout << "Students: " << courses[i].numStudents << endl;

					for(int j = 0; j < courses[i].numStudents; j++) {
						for(int k = 0; k < num_students; k++) {
							if(students[k].bnumber == courses[i].studentArr[j]) {
								cout << students[k].bnumber << " " << students[k].firstName << " " << students[k].lastName << endl;
								break;
							}
						}
					}
				}
			}
		}

		else if(args[0] == "schedule") {
			if(args.size() < 2) {
				cout << "Input Error: too few arguments" << endl;
				continue;
			}
			if(args.size() > 2) {
				cout << "Warning: ignoring extra argument(s)" << endl;
				continue;
			}

			string bnumber = args[1];

			if(!valid_bnumber(bnumber)) {
				cout << "Input Error: illegal B Number" << endl;
				continue;
			}
			
			Student temp;
			for(int i = 0; i < num_students; i++) {
				if(students[i].bnumber == bnumber) {
					temp = students[i];
					cout << "Student: " << students[i].bnumber << ": " << students[i].firstName << " " << students[i].lastName << endl;
					break;
				}
			}

			for(int i = 0; i < temp.numCourses; i++) {
				string crn = temp.courseArr[i];
				for(int j = 0; j < num_courses; j++) {
					if(courses[i].crn == crn) {
						cout << courses[i].crn << " " << courses[i].department << " " << courses[i].number << " " << courses[i].name << endl;
					}
				}
			}
		}
		
		else if(args[0] == "quit") {
			delete[] courses;
			delete[] students;
			return 0;
		}
		else {
			cout << "Input Error: command not recognized, please try again." << endl;
			continue;
		}
	}
}
