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

void storeCancelledReservation();
void restoreReservation();
void displayCancellationHistory();

#endif
