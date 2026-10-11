#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

using namespace std;


#include <string>
#include "Reservation.h"
#include "ReservationList.h"
 
// Outcome of a reservation request. Anything other than RES_OK means the
// request was rejected and nothing was added to the list.
enum ReservationStatus {
    RES_OK,
    RES_INVALID_STUDENT,      // empty / malformed student id
    RES_INVALID_RESOURCE,     // empty id, or unknown to the resource module
    RES_INVALID_DATE,         // not YYYY-MM-DD
    RES_INVALID_TIME,         // hours out of range, or end <= start
    RES_TOO_LONG,             // exceeds MAX_HOURS_PER_BOOKING
    RES_RESOURCE_CONFLICT,    // resource already booked in that window
    RES_STUDENT_CONFLICT,     // student already booked elsewhere at that time
    RES_DAILY_LIMIT,          // student hit MAX_BOOKINGS_PER_DAY
    RES_NOT_FOUND,            // cancel: no such reservation id
    RES_NOT_OWNER             // cancel: id belongs to a different student
};
 
// ---------------------------------------------------------------------------
// ReservationManager
// Owns the linked list of active reservations and enforces the booking rules.
// Knows nothing about the resource catalogue, the waiting-list queue, or the
// cancellation stack - those modules plug in through the seams noted below.
// ---------------------------------------------------------------------------
class ReservationManager {
public:
    // Booking rules.
    static const int MAX_BOOKINGS_PER_DAY   = 2;
    static const int MAX_HOURS_PER_BOOKING  = 4;
    static const int OPENING_HOUR           = 7;   // earliest start
    static const int CLOSING_HOUR           = 22;  // latest end
 
    // Seam for the Resource Management module: a function that answers
    // "does this resource id exist in the catalogue?". Left unset, resource
    // ids are only checked for being non-empty, so this module compiles and
    // runs on its own.
    typedef bool (*ResourceChecker)(const std::string& resourceId);
 
private:
    ReservationList activeReservations;
    int             nextReservationId;
    ResourceChecker resourceChecker;
 
    static bool isValidDate(const std::string& date);
 
public:
    ReservationManager();
 
    void setResourceChecker(ResourceChecker checker);
 
    // ----- required operations -----
 
    // Validate a request without changing anything. Runs the field checks
    // first (O(1)) and then the conflict scans over the list (O(n)).
    ReservationStatus validateRequest(const std::string& studentId,
                                      const std::string& resourceId,
                                      const std::string& date,
                                      int startHour,
                                      int endHour) const;
 
    // Create: validates, then inserts into the linked list. On success the
    // new id is written to newIdOut and RES_OK is returned; on failure
    // newIdOut is set to -1 and the rejection reason is returned.
    // A RES_RESOURCE_CONFLICT or RES_DAILY_LIMIT result is the caller's cue
    // to offer the waiting-list queue.
    ReservationStatus createReservation(const std::string& studentId,
                                        const std::string& resourceId,
                                        const std::string& date,
                                        int startHour,
                                        int endHour,
                                        int& newIdOut);
 
    // Cancel: removes from the linked list and copies the record into
    // cancelledOut, which the cancellation stack then pushes.
    ReservationStatus cancelReservation(int reservationId,
                                        Reservation& cancelledOut);
 
    // Same, but refuses when the reservation belongs to another student.
    ReservationStatus cancelReservation(int reservationId,
                                        const std::string& studentId,
                                        Reservation& cancelledOut);
 
    // Seam for the Cancellation History stack: put a popped reservation back
    // into the active list, keeping its original id. Re-checks conflicts,
    // since the slot may have been taken since the cancellation.
    ReservationStatus restoreReservation(const Reservation& reservation);
 
    // ----- display -----
    void displayActiveReservations() const;
    void displayStudentReservations(const std::string& studentId) const;
    void displayResourceSchedule(const std::string& resourceId,
                                 const std::string& date) const;
 
    // ----- queries used by other modules -----
    const Reservation*     findReservation(int reservationId) const;
    const ReservationList& getActiveReservations() const;
    int                    activeCount() const;
 
    // Human-readable text for a status code.
    static std::string statusMessage(ReservationStatus status);
};
 
#endif // RESERVATIONMANAGER_H 






