#include "pr_check3.h"

class Student {
public:
    Student() {
        bNumber = "";
        priorityMap = map<string, int>();
    }
    Student(string bNumber, string schedule) {
        this->bNumber = bNumber;
        this->schedule = schedule;
    }
    int getPriorityPoints(string course) {
        return priorityMap[course];
    }
    string getBNumber() {
        return bNumber;
    }
    void addPriorityPoints(int num, string course) {
        priorityMap[course] += num;
    }
    void addCourseWithPoints(string course, int priorityPoints) {
        if (inCourse(course)) {
            cout << "Student already added to course waitlist" << endl;
            return;
        }
        priorityMap[course] = priorityPoints;
    }
    bool inCourse(string course) {
        if (priorityMap.count(course) != 0) {
            return true;
        }
        return false;
    }
    void studentEnrolled(string course) {
        priorityMap.erase(course);
        for (auto &pair : priorityMap) {
            pair.second = 0;
        }
    }

private:
    string bNumber;
    string schedule;
    map<string, int> priorityMap;
};

class Waitlist {
public:
    Waitlist(string courseName, string semester) {
        maxHeap.push_back(Student());
        this->courseName = courseName;
        this->semester = semester;
    }

    string getCourse() {
        return courseName;
    }

    int searchStudent(string bNum) {
        if (bNumIndex.count(bNum)) {
            return bNumIndex[bNum];
        }
        return 0;
    }

    Student returnStudent(int index) {
        if (index == 0) {
            return Student();
        }
        return maxHeap[index];
    }

    void addStudent(Student &student, int priorityPoints) {
        if (student.inCourse(courseName)) {
            cout << "Student is already in course waitlist" << endl;
            return;
        }
        maxHeap.push_back(student);
        bNumIndex[student.getBNumber()] = maxHeap.size() - 1;
        student.addCourseWithPoints(courseName, priorityPoints);
        heapifyUp(maxHeap.size() - 1);
    }

    void promoteStudent(string bNumber, int num) {
        int index = searchStudent(bNumber);
        if (index == 0) {
            cout << "Student is not in the waitlist" << endl;
            return;
        }
        maxHeap[index].addPriorityPoints(num, courseName);
        heapifyUp(index);
    }

    void enrollStudent() {
        if (maxHeap.size() == 1) {
            return;
        }
        Student enrolled = maxHeap[1];
        cout << "Enrolling student " << enrolled.getBNumber() << " in course " << courseName << endl;
        enrolled.studentEnrolled(courseName);
        bNumIndex.erase(enrolled.getBNumber());
        swap(maxHeap[1], maxHeap.back());
        maxHeap.pop_back();
        heapifyDown(1);
    }

private:
    vector<Student> maxHeap;
    unordered_map<string, int> bNumIndex;
    int size{};
    string courseName;
    string semester;

    int parent(int i) {
        return (i >> 1);
    }

    int leftChild(int i) {
        return (i << 1);
    }

    int rightChild(int i) {
        return (i << 1) + 1;
    }

    void heapify(int arr[], int n, int i) {
	    int largest = i;
	    int l = leftChild(i);
	    int r = rightChild(i);

    	if (l <= n && arr[l] > arr[largest])
    		largest = l;

    	if (r <= n && arr[r] > arr[largest])
    		largest = r;

    	if (largest != i) {
    		swap(arr[i], arr[largest]);
   		heapify(arr, n, largest);
	}
   }

   void buildHeap(int arr[], int n) {
	for (int i = n / 2; i >= 1; i--) {
		heapify(arr, n, i);
	}
   }

   void heapSort(int arr[], int n) {
	buildHeap(arr, n);
	for (int i = n; i >= 2; i--) {
    		swap(arr[1], arr[i]);
    		heapify(arr, i - 1, 1);
	}
   }

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
    return 0;
}