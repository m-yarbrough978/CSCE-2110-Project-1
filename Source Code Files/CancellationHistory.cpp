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
