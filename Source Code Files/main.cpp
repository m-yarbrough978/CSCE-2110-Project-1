#include "Resource.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>


using namespace std;
int main (){
	
	cout << "+-------------------------------------------+" << endl;
	cout << "|     Computer Science and Engineering      |" << endl;
	cout << "|          CSCE 2110 - Project 1            |" << endl;
	cout << "| Micah Yarbrough micahyarbrough@my.unt.edu |" << endl;
	cout << "|                                           |" << endl;
	cout << "+-------------------------------------------+" << endl << endl;

	ifstream ResrcFile; 				//creates the ResrcFile to be used for reading "resources.txt"
	ResrcFile.open("resources.txt");   //opens "resources.txt" to be read
	
	if(ResrcFile.fail()){ 		//if resources.txt fails to be read
		
		cout << "Error reading the Resource file." << endl << endl; //output error message
		return 0; //exit program
	}
	else{
		cout << "Resource file read successfully." <<endl << endl; //output success message
	}
	
	vector<Resource> resrcVect;
	char line[100];
	string tempStr;
	int count1, count2;
	
	while(ResrcFile.getline(line, 100)){
		
		cout << line << endl << endl;

		/*
		This is a test for seeing if the cstring 'line' is being assigned to the
		lines of "resource.txt". It will be changed later to read the lines for the
		specific information of the resources, which will then be put into resrcVect.
		*/
		
	}

	int choice;
	
	do{
		

		cout << "<<<  Campus Resource Reservation System  >>>" << endl;
		cout << "1. View Resources                           " << endl;
		cout << "2. Create Reservation                       " << endl;
		cout << "3. Cancel Reservation                       " << endl;
		cout << "4. View Waiting List                        " << endl;
		cout << "5. Undo Cancelation                         " << endl;
		cout << "6. Search Reservations                      " << endl;
		cout << "7. Sort Resources                           " << endl;
		cout << "8. Generate Report                          " << endl;
		cout << "9. Exit                                     " << endl << endl;
		
		cout << "Enter your choice: " << endl;
		cin >> choice;
		
		if(choice == 1){
			
			
		}
		else if(choice == 2){
			
			
		}
		else if(choice == 3){
			
			
		}
		else if(choice == 4){
			
			
		}
		else if(choice == 5){
			
			
		}
		else if(choice == 6){
			
			
		}
		else if(choice == 7){
			
			
		}
		else if(choice == 8){
			
			
		}
		else if((choice < 1) || (choice > 9)){
			
			cout << "Invalid System Choice." << endl << endl;
			
		}
		
	}while(choice != 9);
  
 
	cout << "Thank you for using the Campus Reservation system. Goodbye!" << endl;
 
	return 0;
}
