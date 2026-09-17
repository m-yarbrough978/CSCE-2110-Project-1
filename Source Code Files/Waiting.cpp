#include "Waiting.h"
#include <iostream>
#include <string>
/* 

Add student to waiting list : add students to created waiting list (function)
Remove student from waiting list : remove students from created waiting list (function)
Display waiting list : use a print statement to display created waiting list (print Display)

*/
using namespace std;

int main() {

Queue<string> waitingList;

int choice;
string student;

do {
    cout << "\nWaiting List Management System\n";
    cout << "1. Add student\n";
    cout << "2. Remove student\n";
    cout << "3. Display waiting list\n";
    cout << "4. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

  if(choice == 1){
      cout << "Enter student name: ";
      cin >> student;

      waitingList.push(student);

      cout << student << " was added to the waiting list.\n";
  }
  
  else if(choice == 2){
    if(waitingList.empty()){
      cout << "The waiting list is empty.\n";
    }
    else {
       cout << waitingList.front() << " was removed from the waiting list.\n";
       waitingList.pop();
    }
  } 
   
  else if(choice == 3){
    if(waitingList.empty()){
      cout << "The waiting list is empty.\n";
    }
    else {
      queue<string> temp = waitingList;

      cout << "\nWaiting List:\n";

      while (!temp.empty()) {
        cout << temp.front() << endl;
        temp.pop();
      }
    }
  } 
  else if(choice == 4){
    cout << "Goodbye:\n";
  }
  else {
    cout << "Invalid choice.\n";
  }
  
} while (choice != 4);
     
return 0;
}
  
