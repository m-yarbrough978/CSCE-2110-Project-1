#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include <stack>
#include "Reservation.h"

struct CancellationHistory
{
  std::stack<Reservation> reservations;
};

void storeCancelledReservation(CancellationHistory& history, Reservation reservation);

Reservation restoreReservation(CancellationHistory& history);

void displayCancellationHistory(const CancellationHistory& history);

#endif
