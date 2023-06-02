#ifndef SCH_CHEC2K_H
#define SCH_CHECK2_H
#include "pr_check3.h"

class Course{
    public:
        Course(string courseName);
        void addPrereq(Course &course);
        unordered_map<string, vector<Course*>> getPrereqs();
        string getCourseName();
    private:
        unordered_map<string, vector<Course*>> prereqs;
        string courseName;
};

bool sch_check(string prereqfile, string schedfile);

#endif