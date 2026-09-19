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

void addStudent();
void removeStudent();
void displayWaitingList();

#endif
