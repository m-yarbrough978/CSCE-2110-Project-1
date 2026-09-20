#include "Waiting.h"
#include <iostream>
/* 
Add student to waiting list : add students to created waiting list (function)
Remove student from waiting list : remove students from created waiting list (function)
Display waiting list : use a print statement to display created waiting list (print Display)
*/
using namespace std;

void addStudent(Waiting& list, string name, int resourceID)
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
    list students.pop();
}

void displayWaitingList(Waiting& list)
{
    if(list.students.empty()){
        cout << "The waiting list is empty." << endl;
        return;
    }

    cout << "\n--- Waiting List ---" << endl;

    while(list.students.empty()){
        cout << "Student: " << list.students.front().name << " | Resource ID: " << list.students.front().resoruceID << endl;
        list.students.pop();
    }
}




