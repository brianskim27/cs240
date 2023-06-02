#ifndef SCH_CHECK_H
#define SCH_CHECK_H
#include "pr_check3.h"

struct Course
{
    string name;
    string semester;
    //int num_prereqs;
    vector<unordered_set<string>> prereqs;
};

pair<int, int> parseSemester(const string &semester);
bool checkDuplicate(const Course &course, unordered_set<string> &courses_taken_dup);
bool checkBeforePrereq(const Course &course, unordered_map<string, Course> &courses_taken_prereq);
bool checkTooMany(const Course &course, unordered_map<string, int> &courses_in_sem);
bool sch_check(string prereqfile, string schedulefile);

#endif