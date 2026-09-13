#include "Resource.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include <iostream>



using namespace std;
int main (){
	
	cout << "+-------------------------------------------+" << endl;
	cout << "|     Computer Science and Engineering      |" << endl;
	cout << "|          CSCE 2110 - Project 1            |" << endl;
	cout << "| Micah Yarbrough micahyarbrough@my.unt.edu |" << endl;
	cout << "|                                           |" << endl;
	cout << "+-------------------------------------------+" << endl << endl;

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
