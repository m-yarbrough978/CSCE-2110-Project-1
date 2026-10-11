#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

// ---------------------------------------------------------------------------
// Reservation
// A single booking of one resource by one student for a time window on a date.
// Times are whole hours on a 24-hour clock; endHour is exclusive, so
// [9, 11) means 9:00am up to (but not including) 11:00am.
// ---------------------------------------------------------------------------
class Reservation {
private:
    int         reservationId;
    std::string studentId;
    std::string resourceId;
    std::string date;       // format: YYYY-MM-DD
    int         startHour;  // 0 - 23
    int         endHour;    // 1 - 24, exclusive

public:
    Reservation();
    Reservation(int resId,
                const std::string& student,
                const std::string& resource,
                const std::string& resDate,
                int start,
                int end);

    // ----- accessors -----
    int         getReservationId() const;
    std::string getStudentId()     const;
    std::string getResourceId()    const;
    std::string getDate()          const;
    int         getStartHour()     const;
    int         getEndHour()       const;

    // ----- mutators -----
    void setReservationId(int resId);
    void setStudentId(const std::string& student);
    void setResourceId(const std::string& resource);
    void setDate(const std::string& resDate);
    void setStartHour(int start);
    void setEndHour(int end);

    // True when this booking and other use the same resource on the same date
    // with overlapping hours. Back-to-back bookings (9-11 and 11-13) do not
    // overlap. O(1).
    bool overlapsWith(const Reservation& other) const;

    // True when both bookings belong to the same student on the same date and
    // the hours overlap (a student cannot be in two places at once). O(1).
    bool conflictsForStudent(const Reservation& other) const;

    // One formatted line, no newline, suitable for tables.
    std::string toString() const;

    // Prints toString() followed by a newline.
    void display() const;

    // Column header matching the layout of toString().
    static std::string header();
};

#endif // RESERVATION_H
