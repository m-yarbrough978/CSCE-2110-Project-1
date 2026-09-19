#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include "Reservation.h"

struct CancelledReservation
{
  Reservation reservation;
  CancelledReservation* next;
};

struct CancellationHistory
{
  CancelledReservation* top;
};

void storeCancelledReservation(CancellationHistory& history, Reservation reservation);
void restoreReservation(CancellationHistory& history);
void displayCancellationHistory(CancellationHistory& history);

#endif
