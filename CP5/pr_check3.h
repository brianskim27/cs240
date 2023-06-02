#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
using namespace std;

class CoursePrereq
{
private:
    string name;
    string color;
    vector<CoursePrereq *> prereqs;

public:
    CoursePrereq(string name);
    void addPrereq(CoursePrereq *course);
    vector<CoursePrereq *> getPrereqs() const;
    string getName() const;
    string getColor() const;
    void setColor(string color);
};

class GraphOfCourses
{
public:
    GraphOfCourses();
    ~GraphOfCourses();
    void storeValues(string prereq);
    bool DFS();

private:
    unordered_map<string, CoursePrereq *> courses;
    bool DFSVisit(CoursePrereq *course);
};

bool pr_check(string prereqfile);