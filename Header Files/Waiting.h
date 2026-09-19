#ifndef WAITING_H
#define WAITING_H

#include <string>
using namespace std;

struct Student
{
  string name;  
  int resourceID;
  Student* next;
};

struct Waiting
{
  Student* front; 
  Student* rear;
};

void addStudent(Waiting& list, string name, int resourceID);
void removeStudent(Waiting& list);
void displayWaitingList(Waiting& list);

#endif
