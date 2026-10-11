#ifndef WAITING_H
#define WAITING_H

#include <string>
#include <queue>

struct Student
{
  std::string name;  
  std::string resourceID;
};

struct Waiting
{
  std::queue<Student> students;
};

void addStudent(Waiting& list, std::string name, std::string resourceID);
void removeStudent(Waiting& list);
void displayWaitingList(Waiting& list);

#endif
