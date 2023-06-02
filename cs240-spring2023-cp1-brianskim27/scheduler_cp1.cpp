#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main() {
	cout << "Enter [\"build <crn> <department> <number> <name>\"" << endl << "       " << "\"cancel <crn>\"" << endl << "       " <<  "\"enroll <bnumber> <userid> <first> <last>\"" << endl << "       " << "\"add <bnumber> <crn>\"" << endl << "       " << "\"drop <bnumber> <crn>\"" << endl << "       " << "\"roster <crn>\"" << endl << "       " << "\"schedule <bnumber>\"" << endl << "       " << "\"quit\"]" << endl;

	while(true) {
		cout << ": ";
		string input;
		getline(cin, input);
		stringstream ss;
		ss << input;
		string input1;
		ss >> input1;
		
		if(input1 == "build") {
			string input2, input3, input4, input5;
			ss >> input2;
			ss >> input3;
			ss >> input4;
			ss >> input5;
			cout << input1 << " course " << input2 << " " << input3 << " " << input4 << " " << input5 << endl;
		}
		else if(input1 == "cancel") {
			string input2;
			ss >> input2;
			cout << input1 << " course " << input2 << endl;
		}
		else if(input1 == "enroll") {
			string input2, input3, input4, input5;
			ss >> input2;
			ss >> input3;
			ss >> input4;
			ss >> input5;
			cout << input1 << " student " << input2 << " (" << input3 << ") " << input5 << ", " << input4 << endl;
		}
		else if(input1 == "add") {
			string input2, input3;
			ss >> input2;
			ss >> input3;
			cout << input1 << " student " << input2 << " into course " << input3 << endl;
		}
		else if(input1 == "drop") {
			string input2, input3;
			ss >> input2;
			ss >> input3;
			cout << input1 << " student " << input2 << " from course " << input3 << endl;
		}
		else if(input1 == "roster") {
			string input2;
			ss >> input2;
			cout << input1 << " of course " << input2 << endl;
		}
		else if(input1 == "schedule") {
			string input2;
			ss >> input2;
			cout << input1 << " of student " << input2 << endl;
		}
		else if(input1 == "quit") {
			return 0;
		}
		else cout << "Command not recognized, please try again." << endl;
	}
}
