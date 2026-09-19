#include "CancellationHistory.h"
#include <iostream>

using namespace std;

void storeCancelledReservation(CancellationHistory& history, Reservation reservation)
{
  reservation.next = nullptr;
  history.reservations.push(reservation);

  cout << "Reservation " << reservation.id << " was added to cancellation history." << endl;
}

