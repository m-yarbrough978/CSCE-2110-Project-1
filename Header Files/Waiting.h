#ifndef WAITING_H
#define WAITING_H

#include <string>
#include <queue>
using namespace std;

struct Student
{
  string name;  
  int resourceID;
};

struct Waiting
{
  queue<Student> students;
};

void addStudent(Waiting& list, string name, int resourceID);
void removeStudent(Waiting& list);
void displayWaitingList(Waiting& list);

#endif
