#include "CancellationHistory.h"
#include <iostream>

using namespace std;

void storeCancelledReservation(CancellationHistory& history, Reservation reservation)
{
  //doesn't keep old linked-list value
  reservation.next = nullptr;
  history.reservations.push(reservation);

  cout << "Reservation " << reservation.id << " was added to cancellation history." << endl;
}

Reservation restoreReservation(CancellationHistory& history)
{
  if(history.reservations.empty()){
    cout << "There are no cancelled reservations to restore." << endl;

    Reservation emptyReservation = {};
    return emptyReservation;
  }

  Reservation restored = history.reservations.top();

  history.reservations.pop();
  restored.next = nullptr;

  cout << "Reservation " << restored.id << " was restored." << endl;

  return restored;
}

void displayCancellationHistory(CancellationHistory history)
{
  if(history.reservations.empty()){
    std::cout << "No cancellation history." << endl;
    return;
  }

  std::cout << "\n--- Cancellation History ---" << endl;
  std::cout << Reservation::header() << std::endl;

  auto historyCopy = history.reservations;
  
  while(!historyCopy.empty()){
    historyCopy.top.display();
    historyCopy.pop();
  }
}
