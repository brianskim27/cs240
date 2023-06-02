#include "sch_check2.h"

Course::Course(string courseName)
{ // initialized in prereq
    this->courseName = courseName;
}

void Course::addPrereq(Course &course)
{
    prereqs[course.getCourseName()].push_back(&course); // for when there are multple options, such as 314 vs 330, otherwise the vector would not be needed
}

unordered_map<string, vector<Course *>> Course::getPrereqs()
{
    return this->prereqs;
}

string Course::getCourseName()
{
    return this->courseName;
}

pair<int, int> parseSemester(const string &semester)
{
    int year = stoi(semester.substr(0, 4));
    string season = semester.substr(4);
    int sem;

    if (season == "Fall")
    {
        sem = 0;
    }
    else if (season == "Spring")
    {
        sem = 1;
    }
    else if (season == "Summer")
    {
        sem = 2;
    }
    else
    {
        cout << "Error: invalid semester" << endl;
        sem = -1;
    }

    return make_pair(year, sem);
}

bool sch_check(string prereqfile, string schedfile){
        string line;
    unordered_map<string, Course> allCourses; // stores all courses by name and object
    map<string, Course> scheduleCourses;      // courses to be put in schedule
    map<pair<int, int>, int> allSemesters;    // semesters(year, season) and the amt of courses

    // Read prereq file
    ifstream prereq_file(prereqfile);
    if (!prereq_file)
    {
        cout << "could not open prerequisite file" << endl;
        return 1;
    }

    if (!pr_check(prereqfile))
        return 1;

    // add courses to courselist

    while (getline(prereq_file, line))
    {
        string courseName, prereq;

        stringstream ss(line);
        ss >> courseName;

        if (allCourses.count(courseName) == 0)
        {
            allCourses[courseName] = Course(courseName);
        }
        while (ss >> prereq)
        {
            if (allCourses.count(prereq) == 0)
            {
                allCourses[prereq] = Course(prereq);
            }
            allCourses[courseName].addPrereq(allCourses[prereq]);
        }
    }

    ifstream schedule_file(schedfile);
    if (!schedule_file)
    {
        cout << "could not open schedule file" << endl;
        return 1;
    }
    while (getline(schedule_file, line))
    {

        string courseName, semester;

        stringstream ss(line);
        ss >> courseName >> semester;

        pair<int, int> sem = parseSemester(semester);

        if (scheduleCourses.count(courseName) == 0) // check if course has been added to the schedule yet, bullet point 1
        {
            if (allCourses.count(courseName) == 0) // does not have prereqs, all good
            {
                allCourses[courseName] = Course(courseName); // add to all courses
            }
            else
            {
                bool prereqsTaken = true;
                unordered_map<string, vector<Course *>> prereqs = allCourses[courseName].getPrereqs();
                for (auto &prereqOptions : prereqs)
                {
                    bool optionScheduled = false;
                    // iterate over options in vector
                    for (auto &course : prereqOptions.second)
                    {
                        if (scheduleCourses.count(course->getCourseName()) == 0)
                        { // if prereq is in the schedule
                            optionScheduled = true;
                            break;
                        }
                    }
                    if (!optionScheduled)
                    {
                        cout << "Schhedule proposes to take course before prerequisite" << endl;
                        return 1;
                    }
                }
                if (prereqsTaken)
                {
                    allCourses[courseName] = Course(courseName); // add to all courses
                }
            }
        }
        else
        {
            cout << "Schedule includes the same course more than once" << endl;
            return 1;
        } // end of bullet point 1

        allSemesters[{sem.first, sem.second}]++; // increment semester
        if (allSemesters[{sem.first, sem.second}] > 3)
        { // bullet 3, check for too many courses in a semester
            cout << "Schedule proposes too many courses (more than 3) in a semester" << endl;
            return 1;
        }
    }

    return 0;
}
