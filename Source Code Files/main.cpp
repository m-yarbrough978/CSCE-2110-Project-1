#include "Resource.h"
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
#include <limits> 
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
	Resource tempRsrc;
	char line[100];
	string tempStr;
	int lineCount = 1;
	int i;
	
	while(ResrcFile.getline(line, 100)){
		
		int barCount = 0;
		int count, countA, countB, countC;
		
		count = 0;
		countA = 0;
		countB = 0;
		countC = 0;
		
		for(i = 0; i < 100; ++i){
			
			++count;
			
			if(line[i] == '|'){
				
				++barCount;
				
				if(barCount == 1){
					
					tempStr = line;
					tempStr.erase(count - 1);
					tempRsrc.SetID(tempStr);
					countA = count;
				}
				else if(barCount == 2){
					
					tempStr = line;
					tempStr.erase(0, countA);
					
					if((lineCount < 5) || (lineCount == 16)){
						tempStr.erase(14);
					}
					else if((lineCount >= 5) && (lineCount < 9) || (lineCount == 17)){
						tempStr.erase(9);
					}
					else if((lineCount == 9) || (lineCount == 10) || (lineCount == 14) || (lineCount == 18)){
						tempStr.erase(13);
					}
					else if((lineCount == 11) || (lineCount == 19)){
						tempStr.erase(10);
					}
					else if(lineCount == 12){
						tempStr.erase(12);
					}
					else if((lineCount == 13) || (lineCount == 15)){
						tempStr.erase(11);
					}
					else if(lineCount == 20){
						tempStr.erase(16);
					}
					
					tempRsrc.SetName(tempStr);
					countB = count;
				}
				else if(barCount == 3){
					tempStr = line;
					tempStr.erase(0, countB);
					
					if((lineCount < 5) || (lineCount == 16) || (lineCount == 9) || (lineCount == 10) || (lineCount == 18)){
						tempStr.erase(10);
					}
					else if((lineCount >= 5) && (lineCount < 9) || (lineCount == 17)){
						tempStr.erase(6);
					}
					else if((lineCount == 11) || (lineCount == 12) || (lineCount == 13) || (lineCount == 19)){
						tempStr.erase(13);
					}
					else if((lineCount == 14) || (lineCount == 15) || (lineCount == 20)){
						tempStr.erase(20);
					}
					
					tempRsrc.SetType(tempStr);
					countC = count;
					
					tempStr = line;
					tempStr.erase(0,countC);
					tempRsrc.SetStatus(tempStr);
				}
			}
			else if(line[i] != '|'){
				
				continue;
			}
			
		}
		
		resrcVect.push_back(tempRsrc);
		
		++lineCount;
		
	}

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

			cout << "+----------------------------------------------------------------------------+" << endl;
			cout << "|Resource ID |  Resource Name  |    Resource Type    | Resource Availability |" << endl;
			cout << "|----------------------------------------------------------------------------|" << endl;
			
			for(i = 0; i < 20; ++i){
				
				cout << left << "|" << setw(12) << resrcVect[i].GetID() << "|";
				cout << setw(17) << resrcVect[i].GetName() << "|";
				cout << setw(21) << resrcVect[i].GetType() << "|";
				cout << setw(23) << resrcVect[i].GetStatus() << "|" << endl;
				
			}
			
			cout << "+----------------------------------------------------------------------------+" << endl << endl;
			
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
		else if(choice == 9){
			
			
		}
		else if(choice == 10){
			
			
		}
			
		else if((choice < 0) || (choice > 10)){
			
			cout << "Invalid System Choice." << endl << endl;
			
		}
		
	}while(choice != 0);
  
 
	cout << "Thank you for using the Campus Reservation system. Goodbye!" << endl << endl;
 
	return 0;
}
