#include "pr_check3.h"

CoursePrereq::CoursePrereq(string name)
{
    this->name = name;
    this->color = "w";
}

void CoursePrereq::addPrereq(CoursePrereq *course)
{
    prereqs.push_back(course);
}

vector<CoursePrereq *> CoursePrereq::getPrereqs() const
{
    return this->prereqs;
}

string CoursePrereq::getName() const
{
    return this->name;
}

string CoursePrereq::getColor() const
{
    return this->color;
}

void CoursePrereq::setColor(string color)
{
    this->color = color;
}

GraphOfCourses::GraphOfCourses()
{
    courses = unordered_map<string, CoursePrereq *>();
}

GraphOfCourses::~GraphOfCourses()
{
    for (auto &course : courses)
    {
        delete course.second;
    }
    courses.clear();
}

void GraphOfCourses::storeValues(string prereq)
{
    string line;

    ifstream prereqfile(prereq);
    if (!prereqfile)
    {
        cout << "could not open prerequisite file" << endl;
        return;
    }

    while (getline(prereqfile, line))
    {
        string courseName;

        stringstream ss(line);
        ss >> courseName;

        CoursePrereq *course;
        if (courses.find(courseName) == courses.end())
        {
            course = new CoursePrereq(courseName);
            courses[courseName] = course;
        }
        else
        {
            course = courses[courseName];
        }

        string prereqName;
        while (ss >> prereqName)
        {
            CoursePrereq *prereq;
            if (courses.find(prereqName) == courses.end())
            {
                prereq = new CoursePrereq(prereqName);
                courses[prereqName] = prereq;
            }
            else
            {
                prereq = courses[prereqName];
            }

            course->addPrereq(prereq);
        }
    }
}

bool GraphOfCourses::DFS()
{
    for (auto &pair : courses)
    {
        if (pair.second->getColor() == "w")
        {
            if (DFSVisit(pair.second))
            {
                return true;
            }
        }
    }
    return false;
}

bool GraphOfCourses::DFSVisit(CoursePrereq *course)
{
    course->setColor("g");
    for (CoursePrereq *prereq : course->getPrereqs())
    {
        if (prereq->getColor() == "g")
        {
            cout << "Cycle found, prerequisites are invalid" << endl;
            return true;
        }
        else if (prereq->getColor() == "w")
        {
            if (DFSVisit(prereq))
            return true;
        }
    }

    course->setColor("b");
    return false;
}

bool pr_check(string prereqfile){
    GraphOfCourses graph;
    // read in prerequisite file and store in graph
    graph.storeValues(prereqfile);

    // check for cycles in graph
    if (graph.DFS())
    {
        cout << "Cycle found, prerequisites are invalid" << endl;
    }
    else
    {
        cout << "No cycle found, prerequisites are valid" << endl;
    }

    return 0;
}