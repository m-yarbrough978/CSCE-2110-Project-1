#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include <stack>
#include "Reservation.h"
using namespace std;

struct CancellationHistory
{
  stack<Reservation> reservations;
};

void storeCancelledReservation(CancellationHistory& history, Reservation reservation);
Reservation restoreReservation(CancellationHistory& history);
void displayCancellationHistory(CancellationHistory& history);

#endif
