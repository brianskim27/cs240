#include "sch_check.h"

pair<int, int> parseSemester(const string &semester)
{
    int year = stoi(semester.substr(0, 4));
    string season = semester.substr(4);
    int sem;

    if (season == "Spring")
    {
        sem = 0;
    }
    else if (season == "Summer")
    {
        sem = 1;
    }
    else if (season == "Fall")
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

bool checkDuplicate(const Course &course, unordered_set<string> &courses_taken_dup)
{
    if (courses_taken_dup.count(course.name))
    {
        cout << "Error: schedule includes the same course more than once" << endl;
        return true;
    }
    courses_taken_dup.insert(course.name);
    return false;
}

bool checkBeforePrereq(const Course &course, unordered_map<string, Course> &courses_taken_prereq)
{
    for (const auto &prereqOptions : course.prereqs)
    {
        bool optionFilled = false;
        for (const auto &prereq : prereqOptions)
        {
            if (courses_taken_prereq.count(prereq))
            {
                Course prereq_course = courses_taken_prereq[prereq];
                pair<int, int> prereq_sem = parseSemester(prereq_course.semester);
                pair<int, int> course_sem = parseSemester(course.semester);
                if (prereq_sem.first < course_sem.first || (prereq_sem.first == course_sem.first && prereq_sem.second < course_sem.second))
                {
                    optionFilled = true;
                    break;
                }
            }
        }
        if (!optionFilled)
        {
            cout << "Error: schedule proposes to take the course " << course.name << " before its prerequisite ";
            for(const auto &prereq : prereqOptions){
                cout << prereq << " ";
            }
            cout << endl;
            return true;
        }
    }
    return false;
}

bool checkTooMany(const Course &course, unordered_map<string, int> &courses_in_sem)
{
    int year, sem;
    tie(year, sem) = parseSemester(course.semester);
    if (sem < 0)
    {
        return false;
    }

    int count = courses_in_sem[course.semester]++;
    if (count > 3)
    {
        cout << "Error: schedule proposes too many courses (more than 3) in a semester" << endl;
        return true;
    }
    return false;
}

bool sch_check(string prereqfile, string schedulefile)
{
    // Read prereq file
    ifstream prereq_file(prereqfile);
    if (!prereq_file)
    {
        cout << "could not open prerequisite file" << endl;
        return true;
    }
    unordered_map<string, Course> courses;
    string line;
    Course course;
    while (getline(prereq_file, line))
    {
        cout << "option" << endl;
        string name;

        stringstream ss(line);
        ss >> name;

        string prereqName;
        vector<unordered_set<string>> prereqs;
        unordered_set<string> option;

        while (ss >> prereqName)
        {
            option.insert(prereqName);
            prereqs.push_back(option);
            cout << prereqName << "added of course " << name << endl;

        }

        course.name = name;
        course.prereqs = prereqs;
        courses[name] = course;

        /*string name = line.substr(0, 6);
        int num_prereqs = stoi(line.substr(7));
        unordered_set<string> prereqs;
        for (int i = 0; i < num_prereqs; i++)
        {
            getline(prereq_file, line);
            prereqs.insert(line);
        }
        courses[name] = {name, "", num_prereqs, prereqs}; */
    }
    prereq_file.close();

    // Read schedule file
    ifstream schedule_file(schedulefile);
    if (!schedule_file)
    {
        cout << "could not open schedule file" << endl;
        return false;
    }
    unordered_map<string, int> courses_in_sem;
    unordered_map<string, Course> courses_taken_prereq;
    unordered_set<string> courses_taken_dup;

    while (getline(schedule_file, line))
    {
        string name, semester;

        stringstream ss(line);
        ss >> name >> semester;

        

        if (courses.count(name) == 0)
        {
            cout << "Error: schedule proposes to take an invalid course" << endl;
            return false;
        }

        Course course = courses[name];
        course.semester = semester;
        if (checkDuplicate(course, courses_taken_dup) || checkBeforePrereq(course, courses_taken_prereq) || checkTooMany(course, courses_in_sem))
        {
            return false;
        }
        courses_taken_prereq[name] = course;
    }
    schedule_file.close();

    // If no errors, the proposed schedule is valid
    cout << "Proposed schedule is valid" << endl;
    return true;
}