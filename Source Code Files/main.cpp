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
#include <limits> 
using namespace std; 

void mergeResources(vector<Resources>& resources, int left, int mid, int right)
{
	vector<Resource> temp;
	int i = left;
	int j = mid +1;

	// Merge the two sorted halves
	while(i <= mid && j <= right)
	{
		if(resources[i].GetName() <= resources[j].GetNmae())
		{
			temp.push_back(resources[i]);
			++i;
		}
		else
		{
			temp.push_back(resources[j]);
			++j;
		}
	}

	// Copy any remaining resources from the left half
	while (i <= mid)
	{
		temp.push_back(resources[i]);
		++i;
	}

	// Copy any remaining resources from the right half
	while (j <= right)
	{
		temp.push_back(resources[j]);
		++j;
	}
	// Copy the merged resources back into the original vector.
	for(int k =0; k < static_cast<int>(temp.size()); ++k)
	{
	resources[left+k] = temp[k];
	}
}

void mergeSortResources(vector<Resource>& resources, int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int mid = left +(right - left) / 2;

	mergeSortResources(resources, left, mid);
	mergeSortResources(resources, mid + 1, right);
	mergeSortResources(resources, left, mid, right);
}

int main (){

	Waiting list;
	CancellationHistory history;
	ReservationManager resrvList;
	
	cout << "+--------------------------------------------------+" << endl;
	cout << "|         Computer Science and Engineering         |" << endl;
	cout << "|              CSCE 2110 - Project 1               |" << endl;
	cout << "|     Micah Yarbrough micahyarbrough@my.unt.edu    |" << endl;
	cout << "| Dabira olubobola OluwadabiraOlubobola@my.unt.edu |" << endl; 
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
	vector<Resource> IDsortedResrcVec;
	ResourceManager resrcMan;

	resrcVect = resrcMan.createVector(ResrcFile);
	IDsortedResrcVec = resrcVect;

	string choice;
	int newIDOut = 0;
	
	do{
		
		cout << endl;
		cout << "<<<  Campus Resource Reservation System  >>>" << endl;
		cout << "1. View Resources                           " << endl;
		cout << "2. Search Resources                         " << endl;
		cout << "3. Sort Resources                           " << endl;
		cout << "4. Create Reservation                       " << endl;
		cout << "5. Cancel Reservation                       " << endl;
		cout << "6. Add Students to Waiting List             " << endl;
		cout << "7. Remove Students from Waiting List        " << endl;
		cout << "8. Display Waiting List                     " << endl;
		cout << "9. Restore Cancellation                     " << endl;
		cout << "10. Display Cancellation History            " << endl;
		cout << "11. Sort Resources                          " << endl;
		cout << "12. Generate Report                         " << endl;
		cout << "0. Exit                                     " << endl << endl;
		
		cout << "Enter your choice: ";
		cin >> choice;
		
		if(choice == "1"){

			resrcMan.Print(resrcVect);
			
		}
		else if(choice == "2"){
			
			string resrcID;
			Resource tempResource;
			
			cout << "Enter Resource ID (ex: R100): " << endl;
			cin >> resrcID;
			
			tempResource = resrcMan.SearchByID(resrcVect, resrcID);
	
			cout << endl;
			cout << "+----------------------------------------------------------------------------+" << endl;
			cout << "|Resource ID |  Resource Name  |    Resource Type    | Resource Availability |" << endl;
			cout << "|----------------------------------------------------------------------------|" << endl;
			cout << left << "|" << setw(12) << tempResource.GetID() << "|";
			cout << setw(17) << tempResource.GetName() << "|";
			cout << setw(21) << tempResource.GetType() << "|";
			cout << setw(23) << tempResource.GetStatus() << "|" << endl;
			cout << "+----------------------------------------------------------------------------+" << endl << endl;

		}
		else if(choice == "3"){

			cout << endl;
			cout << "What would you like to sort by?" << endl;
			cout << "I - ID" << endl;
			cout << "N - Name" << endl;
			cout << "T - Type" << endl;
			cout << "A - Availability" << endl;
			
			cin >> choice;
			
			if((choice == "I") || (choice == "i") || (choice == "N") || (choice == "n") || (choice == "T") || (choice == "t") || (choice == "A") || (choice == "a")){
				
				resrcMan.sort(choice, resrcVect, 0, 19);
				cout << endl << "Use Menu Option 1 to view the sorted resources." << endl;
				
			}
			else{
				
				cout << endl << "Invalid Resource Identifier." << endl;
				
			}
			
			cout << "+----------------------------------------------------------------------------+" << endl << endl;
			
		}
		else if(choice == "2"){
			string studentID, resourceID, date;
			int startHour, endHour;
			
			cout << endl << "Enter Student ID: ";
			cin >> studentID;
			cout << endl << "Enter Resource ID: ";
			cin >> resourceID;
			cout << endl << "Enter date (YYYY-MM-DD): ";
			cin >> date;
			cout << endl << "Enter start hour: ";
			cin >> startHour;
			cout << endl << "Enter end hour: ";
			cin >> endHour;
			
			ReservationStatus status = resrvList.createReservation(
				studentID, resourceID, date, startHour, endHour, newIDOut);

			cout << ReservationManager::statusMessage(status) << endl;

			if(status == RES_OK) { 
				cout << "Reservation ID: " << newIDOut << endl;
			}
		
			cout << endl;
			
		}
		else if(choice == "3"){
			int resrvID;
			Reservation cancelledOut;
			
			cout << endl << "Enter reservation ID: ";
			cin >> resrvID;
			ReservationStatus status = resrvList.cancelReservation(resrvID, cancelledOut);

			cout << ReservationManager::statusMessage(status) << endl;

			if(status == RES_OK) {
				storeCancelledReservation(history, cancelledOut);
				
			cout << endl;
			
		}
		else if(choice == "4"){
			string studentName, resourceID;

			cout << "Enter student name: ";
			cin >> studentName;

			cout << "Enter resource ID: ";
			cin >> resourceID;

			addStudent(list, studentName, resourceID);	
		}
		else if(choice == "5"){
			removeStudent(list);
		}
		else if(choice == "6"){
			displayWaitingList(list);	
		}
		else if(choice == "7"){
			Reservation restored = restoreReservation(history);

			ReservationStatus status = resrvList.restoreReservation(restored);

			if(status == RES_OK) {
				cout << "Reservation restored successfully." << endl;
			}
			else {
				cout << "Restoration failed: " << ReservationManager::statusMessage(status) << endl;

				history.reservations.push(restored);
			
		}
		else if(choice == "10"){
			displayCancellationHistory(history);
			
		}
		else if(choice != "0")){
			
			cout << "Invalid System Choice." << endl;
			
		}
		
	}while(choice != "0");
  
 
	cout << endl << "Thank you for using the Campus Reservation system. Goodbye!" << endl << endl;
 
	return 0;
}
