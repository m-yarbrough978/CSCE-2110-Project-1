

#include "ReservationManager.h"
#include <iostream>
#include <string>
#include "ReservationManager.h"
 
#include <iostream>
#include <cctype>
 
ReservationManager::ReservationManager()
    : activeReservations(), nextReservationId(1001), resourceChecker(nullptr) {
}
 
void ReservationManager::setResourceChecker(ResourceChecker checker) {
    resourceChecker = checker;
}
 
bool ReservationManager::isValidDate(const std::string& date) {
    // Expected layout: YYYY-MM-DD
    if (date.length() != 10)               return false;
    if (date[4] != '-' || date[7] != '-')  return false;
 
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(static_cast<unsigned char>(date[i]))) return false;
    }
 
    int month = (date[5] - '0') * 10 + (date[6] - '0');
    int day   = (date[8] - '0') * 10 + (date[9] - '0');
    if (month < 1 || month > 12) return false;
    if (day   < 1 || day   > 31) return false;
 
    return true;
}
 
ReservationStatus ReservationManager::validateRequest(const std::string& studentId,
                                                      const std::string& resourceId,
                                                      const std::string& date,
                                                      int startHour,
                                                      int endHour) const {
    // --- field checks, all O(1) ---
    if (studentId.empty())  return RES_INVALID_STUDENT;
    if (resourceId.empty()) return RES_INVALID_RESOURCE;
 
    if (resourceChecker != nullptr && !resourceChecker(resourceId)) {
        return RES_INVALID_RESOURCE;
    }
 
    if (!isValidDate(date)) return RES_INVALID_DATE;
 
    if (startHour < OPENING_HOUR || endHour > CLOSING_HOUR || endHour <= startHour) {
        return RES_INVALID_TIME;
    }
    if (endHour - startHour > MAX_HOURS_PER_BOOKING) {
        return RES_TOO_LONG;
    }
 
    // --- rule checks that need the list, each one traversal ---
    if (activeReservations.countForStudent(studentId, date) >= MAX_BOOKINGS_PER_DAY) {
        return RES_DAILY_LIMIT;
    }
    if (activeReservations.hasResourceConflict(resourceId, date, startHour, endHour)) {
        return RES_RESOURCE_CONFLICT;
    }
    if (activeReservations.hasStudentConflict(studentId, date, startHour, endHour)) {
        return RES_STUDENT_CONFLICT;
    }
 
    return RES_OK;
}
 
ReservationStatus ReservationManager::createReservation(const std::string& studentId,
                                                        const std::string& resourceId,
                                                        const std::string& date,
                                                        int startHour,
                                                        int endHour,
                                                        int& newIdOut) {
    ReservationStatus status = validateRequest(studentId, resourceId, date,
                                               startHour, endHour);
    if (status != RES_OK) {
        newIdOut = -1;
        return status;
    }
 
    Reservation booking(nextReservationId, studentId, resourceId,
                        date, startHour, endHour);
    activeReservations.insert(booking);
 
    newIdOut = nextReservationId;
    nextReservationId++;
    return RES_OK;
}
 
ReservationStatus ReservationManager::cancelReservation(int reservationId,
                                                        Reservation& cancelledOut) {
    if (activeReservations.remove(reservationId, cancelledOut)) {
        return RES_OK;
    }
    return RES_NOT_FOUND;
}
 
ReservationStatus ReservationManager::cancelReservation(int reservationId,
                                                        const std::string& studentId,
                                                        Reservation& cancelledOut) {
    const Reservation* target = activeReservations.find(reservationId);
    if (target == nullptr)                     return RES_NOT_FOUND;
    if (target->getStudentId() != studentId)   return RES_NOT_OWNER;
 
    activeReservations.remove(reservationId, cancelledOut);
    return RES_OK;
}
 
ReservationStatus ReservationManager::restoreReservation(const Reservation& reservation) {
    if (activeReservations.find(reservation.getReservationId()) != nullptr) {
        return RES_OK;   // already active, nothing to do
    }
 
    if (activeReservations.hasResourceConflict(reservation.getResourceId(),
                                               reservation.getDate(),
                                               reservation.getStartHour(),
                                               reservation.getEndHour())) {
        return RES_RESOURCE_CONFLICT;
    }
    if (activeReservations.hasStudentConflict(reservation.getStudentId(),
                                              reservation.getDate(),
                                              reservation.getStartHour(),
                                              reservation.getEndHour())) {
        return RES_STUDENT_CONFLICT;
    }
 
    activeReservations.insert(reservation);
    return RES_OK;
}
 
void ReservationManager::displayActiveReservations() const {
    std::cout << "ACTIVE RESERVATIONS" << std::endl;
    activeReservations.display();
}
 
void ReservationManager::displayStudentReservations(const std::string& studentId) const {
    std::cout << "RESERVATIONS FOR STUDENT " << studentId << std::endl;
    activeReservations.displayForStudent(studentId);
}
 
void ReservationManager::displayResourceSchedule(const std::string& resourceId,
                                                 const std::string& date) const {
    std::cout << "SCHEDULE FOR " << resourceId << " ON " << date << std::endl;
 
    bool anyBooked = false;
    for (int hour = OPENING_HOUR; hour < CLOSING_HOUR; hour++) {
        bool busy = activeReservations.hasResourceConflict(resourceId, date,
                                                           hour, hour + 1);
        std::cout << "  " << hour << ":00 - " << (hour + 1) << ":00  "
                  << (busy ? "BOOKED" : "open") << std::endl;
        if (busy) anyBooked = true;
    }
    if (!anyBooked) {
        std::cout << "  (resource is free all day)" << std::endl;
    }
}
 
const Reservation* ReservationManager::findReservation(int reservationId) const {
    return activeReservations.find(reservationId);
}
 
const ReservationList& ReservationManager::getActiveReservations() const {
    return activeReservations;
}
 
int ReservationManager::activeCount() const {
    return activeReservations.size();
}
 
std::string ReservationManager::statusMessage(ReservationStatus status) {
    switch (status) {
        case RES_OK:                return "Request accepted.";
        case RES_INVALID_STUDENT:   return "Student ID is missing or invalid.";
        case RES_INVALID_RESOURCE:  return "Resource ID is missing or not in the catalogue.";
        case RES_INVALID_DATE:      return "Date must be in YYYY-MM-DD format.";
        case RES_INVALID_TIME:      return "Time window is outside opening hours or ends before it starts.";
        case RES_TOO_LONG:          return "Booking exceeds the maximum length allowed.";
        case RES_RESOURCE_CONFLICT: return "Resource is already booked during that time.";
        case RES_STUDENT_CONFLICT:  return "Student already has a booking during that time.";
        case RES_DAILY_LIMIT:       return "Student has reached the daily booking limit.";
        case RES_NOT_FOUND:         return "No active reservation with that ID.";
        case RES_NOT_OWNER:         return "That reservation belongs to another student.";
        default:                    return "Unknown status.";
    }
}
using namespace std;



