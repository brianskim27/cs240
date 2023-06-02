#include "sch_check.h"


class Student
{
public:
    Student()
    {
        bNumber = -1;
        priorityMap = map<string, int>();
    };
    Student(string bNumber, string schedule)
    {
        this->bNumber = bNumber;
    };
    int getPriorityPoints(string course)
    {
        return priorityMap[course];
    };
    string getBNumber()
    {
        return bNumber;
    };
    void addPriorityPoints(int num, string course)
    {
        this->priorityMap[course] += num;
    };
    void addCourseWithPoints(string course, int priorityPoints)
    {
        if (inCourse(course))
        {
            cout << "student already added to course waitlist" << endl;

            return;
        }

        priorityMap[course] = priorityPoints;
    };
    bool inCourse(string course)
    {
        if (priorityMap.count(course) != 0)
        {
            return 0; // student is in course
        }

        return 1;
    };
    void studentEnrolled(string course)
    {
        priorityMap.erase(course);

        for (auto &pair : priorityMap)
        {
            pair.second = 0; // set all other priorityvalues of other waitlisted classes to 0
        }
    }

private:
    string bNumber;
    string schedule;
    map<string, int> priorityMap; // course, priorityPoints associated
};

class Waitlist
{
public:
    Waitlist(string courseName, string semester)
    {
        maxHeap = {Student()};
        this->courseName = courseName;
        this->semester = semester;
    };

    string getCourse()
    {
        return courseName;
    };

    int searchStudent(string bNum)
    {
        if (bNumIndex.count(bNum))
        {
            return bNumIndex[bNum];
        }
        return 0; // O(1)
    }

    Student returnStudent(int index)
    {
        if (index == 0)
            return Student();
        return maxHeap[index];
    }
    void addStudent(Student &student, int priorityPoints)
    { // same as inserting

        maxHeap[size++] = student; // O(1)

        if (student.inCourse(courseName))
        {
            cout << "student is already in course waitlist" << endl;
            return;
        }

        student.addCourseWithPoints(courseName, priorityPoints);
        bNumIndex[student.getBNumber()] = size;

        heapifyUp(size);
        return;
    };
    void promoteStudent(string bNumber, int num)
    { // same as increaase keyr

        int index = searchStudent(bNumber);

        maxHeap[index].addPriorityPoints(num, courseName);

        if (index != 0)
        {
            heapifyUp(index);
        }
        return;
    };
    void enrollStudent()
    { // same as extract max
        if (maxHeap.empty())
            return;

        cout << "Enrolling student " << maxHeap[1].getBNumber() << " in course " << courseName << endl;

        maxHeap[1].studentEnrolled(courseName); // deletes course from student itself, sets priority of other classes to 0

        bNumIndex.erase(maxHeap[1].getBNumber());

        swap(maxHeap[1], maxHeap[size--]);

        maxHeap.pop_back();

        heapifyDown(1); // rearrange tree properly
    };

private:
    vector<Student> maxHeap;
    unordered_map<string, int> bNumIndex; // for fast index/bnum search
    int size{};
    string courseName;
    string semester;
    int parent(int i)
    {
        return (i >> 1);
    };
    int leftChild(int i)
    {
        return (i << 1);
    };
    int rightChild(int i)
    {
        return ((i << 1) + 1);
    };
    void heapifyUp(int i)
    {
        if (i > size)
            return;
        if (i == 1)
            return;

        if (maxHeap[i].getPriorityPoints(getCourse()) > maxHeap[parent(i)].getPriorityPoints(getCourse()))
        {
            swap(maxHeap[parent(i)], maxHeap[i]);
        }

        heapifyUp(parent(i));
    };
    void heapifyDown(int i)
    {
        if (i > size)
            return;

        int largest = i;

        if ((leftChild(i) <= size) && (maxHeap[i].getPriorityPoints(getCourse()) < maxHeap[leftChild(i)].getPriorityPoints(getCourse())))
        {
            largest = leftChild(i);
        }

        if ((rightChild(i) <= size) && (maxHeap[i].getPriorityPoints(getCourse()) < maxHeap[rightChild(i)].getPriorityPoints(getCourse())))
        {
            largest = rightChild(i);
        }

        if (largest != i)
        {
            swap(maxHeap[i], maxHeap[largest]);
            heapifyDown(largest);
        }
        return;
    };
};

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        cout << "format: ./waitlist <semester> <prereqfile> <schedsfile> <enrollmentfile>" << endl;
        return 1;
    }

    vector<Waitlist> allWaitlists;    // stores all waitlists for courses
    map<string, Student> allStudents; // stores all students, <bNum, student>

    string semester = argv[1];

    ifstream prereqfile(argv[2]); // open prereq file NOT DONE
    if (!prereqfile)
    {
        cout << "could not open prerequisite file" << endl;
        return 1;
    }

    string line;

    if (pr_check(argv[2]))
    {
        ifstream schedulefile(argv[3]); // open schedule file NOT DONE
        if (!schedulefile)
        {
            cout << "could not open schedule file" << endl;
            return 1;
        }

        while (getline(schedulefile, line))
        {
            string bNum, studentSchedule;

            stringstream ss(line);
            ss >> bNum >> studentSchedule;

            if (allStudents.count(bNum) == 0)
            {
                // check schedule validity using sched checker, o file shit
                if (sch_check(argv[2], studentSchedule))
                {

                    allStudents[bNum] = Student(bNum, studentSchedule); // add student to list of existing students}
                }
                else
                {
                    cout << "student already exists, skipping" << endl;
                }
            }

            ifstream enrollmentfile(argv[4]); // open enrollment file
            if (!enrollmentfile)
            {
                cout << "could not open enrollment file" << endl;
                return 1;
            }

            while (getline(enrollmentfile, line))
            {
                string action, bNum, course;
                int priorityPoints;
                stringstream ss(line);

                ss >> action;
                if (action.compare("newlist") || action.compare("enroll"))
                {
                    ss >> course;
                }
                else
                {
                    ss >> bNum >> course >> priorityPoints;
                }

                if (action.compare("newlist"))
                {
                    Waitlist waitlist(course, semester); // create new waitlist with course
                    allWaitlists.push_back(waitlist);
                }
                else if (action.compare("add"))
                { // add student to already existing waitlist, waitlist actions may not necessarily be in order
                    if (allStudents.count(bNum) != 0)
                    {
                        for (Waitlist waitlist : allWaitlists)
                        {
                            if (waitlist.getCourse() == course)
                            {
                                allStudents[bNum].addCourseWithPoints(course, priorityPoints);
                                waitlist.addStudent(allStudents[bNum], priorityPoints);
                            }
                        }
                    }
                }
                else if (action.compare("promote"))
                { // change priority queue of student
                    for (Waitlist waitlist : allWaitlists)
                    {
                        if (waitlist.getCourse() == course)
                        {
                            if (waitlist.searchStudent(bNum) != 0)
                            {
                                waitlist.promoteStudent(bNum, priorityPoints);
                            }
                        }
                    }
                }
                else if (action.compare("enroll"))
                {
                    for (Waitlist waitlist : allWaitlists)
                    {
                        if (waitlist.getCourse() == course)
                        {
                            waitlist.enrollStudent();
                        }
                    }
                }
            }
        }
    }
    allWaitlists.clear();
}