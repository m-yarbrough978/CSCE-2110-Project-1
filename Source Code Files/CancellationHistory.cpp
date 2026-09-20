#include "CancellationHistory.h"
#include <iostream>

using namespace std;

void storeCancelledReservation(CancellationHistory& history, Reservation reservation)
{
  history.reservations.push(reservation);

  cout << "Reservation " << reservation.getReservationId() << " was added to cancellation history." << endl;
}

Reservation restoreReservation(CancellationHistory& history)
{
  if(history.reservations.empty()){
    cout << "There are no cancelled reservations to restore." << endl;

    Reservation emptyReservation;
    return emptyReservation;
  }

  Reservation restored = history.reservations.top();

  history.reservations.pop();

  cout << "Reservation " << restored.getReservationId() << " was restored." << endl;

  return restored;
}

void displayCancellationHistory(CancellationHistory& history)
{
  if(history.reservations.empty()){
    cout << "No cancellation history." << endl;
    return;
  }

  cout << "\n--- Cancellation History ---" << endl;

  stack<Reservation> temp = history.reservations;

  while(!temp.empty()){
    Reservation reservation = temp.top();

    cout << "Reservation ID: " << reservation.getReservationId() << endl;

    cout << "Student: " << reservation.getStudentId() << endl;

    cout << "Resource ID: " << reservation.getResourceId() << endl;

    cout << "Date: " << reservation.getDate() << endl;

    cout << "Start Time: " << reservation.getStartHour() << ":00" << endl;

    cout << "End Time: " << reservation.getEndHour() << ":00" << endl;

    cout << endl;

    temp.pop();
  }
}
