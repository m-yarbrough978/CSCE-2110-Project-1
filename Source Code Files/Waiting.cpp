#include "Waiting.h"
#include <iostream>
/* 
Add student to waiting list : add students to created waiting list (function)
Remove student from waiting list : remove students from created waiting list (function)
Display waiting list : use a print statement to display created waiting list (print Display)
*/
using namespace std;

void addStudent(Waiting& list, string name, string resourceID)
{
    Student student;

    student.name = name;
    student.resourceID = resourceID;

    list.students.push(student);

    cout << name << " was added to the waiting list." << endl;
}

void removeStudent(Waiting& list)
{
    if(list.students.empty()){
        cout << "The waiting list is empty." << endl;
        return;
    }

    cout << list.students.front().name << " was removed from the waiting list." << endl;
    list.students.pop();
}

void displayWaitingList(Waiting& list)
{
    if(list.students.empty()){
        std::cout << "The waiting list is empty." << endl;
        return;
    }

    std::cout << "\n--- Waiting List ---" << endl;

    auto studentCopy = list.students;

    while(!studentCopy.empty()){
        const Student& student = studentsCopy.front();

        
        std::cout << "Student: " << student.name << " | Resource ID: " << student.resourceID << std::endl;
        
        studentsCopy.pop();
    }
}

int countWaitingForResource(const Waiting& list, const std::string& resourceID) {
    int count = 0;

    // Copy the queue so the original waiting list is preserved.
   queue<Student> studentsCopy = list.students;

    while(!studentsCopy.empty()) {
        if(studentsCopy.front().resourceID == resourceID) {
            ++count;
        }

        studentsCopy.pop();
    }

    return count;
}

//Count all students in the waiting list.
int countWaitingStudents(const Waiting& list){
    return static_cast<int>(list.students.size());
}



