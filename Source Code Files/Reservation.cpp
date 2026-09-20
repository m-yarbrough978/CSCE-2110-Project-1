#include "Reservation.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
Reservation::Reservation()
    : reservationId(0), studentId(""), resourceId(""), date(""),
      startHour(0), endHour(0) {
}
 
Reservation::Reservation(int resId,
                         const std::string& student,
                         const std::string& resource,
                         const std::string& resDate,
                         int start,
                         int end)
    : reservationId(resId), studentId(student), resourceId(resource),
      date(resDate), startHour(start), endHour(end) {
}
 
// ----- accessors -----
int         Reservation::getReservationId() const { return reservationId; }
std::string Reservation::getStudentId()     const { return studentId; }
std::string Reservation::getResourceId()    const { return resourceId; }
std::string Reservation::getDate()          const { return date; }
int         Reservation::getStartHour()     const { return startHour; }
int         Reservation::getEndHour()       const { return endHour; }
 
// ----- mutators -----
void Reservation::setReservationId(int resId)                { reservationId = resId; }
void Reservation::setStudentId(const std::string& student)   { studentId = student; }
void Reservation::setResourceId(const std::string& resource) { resourceId = resource; }
void Reservation::setDate(const std::string& resDate)        { date = resDate; }
void Reservation::setStartHour(int start)                    { startHour = start; }
void Reservation::setEndHour(int end)                        { endHour = end; }
 
bool Reservation::overlapsWith(const Reservation& other) const {
    if (resourceId != other.resourceId) return false;
    if (date != other.date)             return false;
    // Half-open intervals: overlap only when each starts before the other ends.
    return (startHour < other.endHour) && (other.startHour < endHour);
}
 
bool Reservation::conflictsForStudent(const Reservation& other) const {
    if (studentId != other.studentId) return false;
    if (date != other.date)           return false;
    return (startHour < other.endHour) && (other.startHour < endHour);
}
 
std::string Reservation::toString() const {
    std::ostringstream out;
    out << std::left
        << std::setw(8)  << reservationId
        << std::setw(12) << studentId
        << std::setw(12) << resourceId
        << std::setw(14) << date
        << std::right << std::setw(3) << startHour << ":00"
        << " - "
        << std::setw(3) << endHour << ":00";
    return out.str();
}
 
void Reservation::display() const {
    std::cout << toString() << std::endl;
}
 
std::string Reservation::header() {
    std::ostringstream out;
    out << std::left
        << std::setw(8)  << "ID"
        << std::setw(12) << "STUDENT"
        << std::setw(12) << "RESOURCE"
        << std::setw(14) << "DATE"
        << "TIME";
    return out.str();
}



