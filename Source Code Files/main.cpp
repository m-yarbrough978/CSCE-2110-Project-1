#include "Resource.h"
#include "ResourceManager.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include "Reservationlist.h"
#include "Waiting.h"
#include "CancellationHistory.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>


using namespace std;

int main (){

	Waiting list;
	CancellationHistory history;
	
	cout << "+--------------------------------------------------+" << endl;
	cout << "|         Computer Science and Engineering         |" << endl;
	cout << "|              CSCE 2110 - Project 1               |" << endl;
	cout << "|     Micah Yarbrough micahyarbrough@my.unt.edu    |" << endl;
	cout << "| Dabira olubobola Oluwadabiraolubobola@my.unt.edu |" << endl; 
	cout << "|    Jayden Thompson jaydenthompson2@my.unt.edu    |" << endl;
	cout << "+--------------------------------------------------+" << endl << endl;

	ifstream ResrcFile; 				//creates the ResrcFile to be used for reading "resources.txt"
	ResrcFile.open("resources.txt");   //opens "resources.txt" to be read

	ifstream ResFile;
	ResFile.open("reservations.txt");
	
	if(ResrcFile.fail() && ResFile.fail()){ 		//if resources.txt fails to be read
		
		cout << "Error reading the Resource file and Reservation file." << endl << endl; //output error message
		return 0; //exit program
	}
	else if(ResrcFile.fail()){
		cout << "Error reading the Resource file." << endl << endl; //output error message
		return 0; //exit program
	}
	else if(ResFile.fail()){
		cout << "Error reading the Reservation file." << endl << endl; //output error message
		return 0;
	}
	else{
		cout << "Resource file and Reservation file read successfully." <<endl << endl; //output success message
	}
	
	vector<Resource> resrcVect;
	ResourceManager resrcMan;

	resrcVect = resrcMan.createVector(ResrcFile);

	int choice;
	
	do{
		

		cout << "<<<  Campus Resource Reservation System  >>>" << endl;
		cout << "1. View Resources                           " << endl;
		cout << "2. Create Reservation                       " << endl;
		cout << "3. Cancel Reservation                       " << endl;
		cout << "4. Add Students to Waiting List             " << endl;
		cout << "5. Remove Students from Waiting List        " << endl;
		cout << "6. Display Waiting List                     " << endl;
		cout << "7. Restore Cancellation                     " << endl;
		cout << "8. Display Cancellation History             " << endl;
		cout << "9. Sort Resources                           " << endl;
		cout << "10. Generate Report                          " << endl;
		cout << "0. Exit                                     " << endl << endl;
		
		cout << "Enter your choice: ";
		cin >> choice;
		
		if(choice == 1){

			resrcMan.Print(resrcVect);
			
		}
		else if(choice == 2){
			
			
		}
		else if(choice == 3){
			
			
		}
		else if(choice == 4){
			string studentName;
			int resourceID;

			cout << "Enter student name: ";
			cin >> studentName;

			cout << "Enter resource ID: ";
			cin >> resourceID;

			addStudent(list, studentName, resourceID);	
		}
		else if(choice == 5){
			removeStudent(list);
		}
		else if(choice == 6){
			displayWaitingList(list);	
		}
		else if(choice == 7){
			Reservation restored = restoreReservation(history);
			
		}
		else if(choice == 8){
			displayCancellationHistory(history);
			
		}
		else if((choice < 0) || (choice > 10)){
			
			cout << "Invalid System Choice." << endl << endl;
			
		}
		
	}while(choice != 0);
  
 
	cout << "Thank you for using the Campus Reservation system. Goodbye!" << endl;
 
	return 0;
}
