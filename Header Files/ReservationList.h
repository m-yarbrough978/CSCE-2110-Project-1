#ifndef RESERVATIONLIST_H
#define RESERVATIONLIST_H

#include <string>
#include "Reservation.h"

// ---------------------------------------------------------------------------
// ReservationList
// Singly linked list holding every ACTIVE reservation. Written by hand (no
// STL container) because the milestone requires a linked list implementation.
//
// The list is kept in chronological order: date, then start hour, then
// reservation id as a tie-breaker. Ordered insertion costs one traversal but
// means display() is already sorted and conflict scans can be read in order.
// ---------------------------------------------------------------------------
class ReservationList {
private:
    struct Node {
        Reservation data;
        Node*       next;
        Node(const Reservation& r) : data(r), next(nullptr) {}
    };

    Node* head;
    int   count;

    // True when a belongs strictly before b in chronological order.
    static bool isBefore(const Reservation& a, const Reservation& b);

public:
    ReservationList();

    // Rule of Three - the list owns raw heap nodes.
    ReservationList(const ReservationList& other);
    ReservationList& operator=(const ReservationList& other);
    ~ReservationList();

    // ----- required operations -----

    // Insert: places the reservation in chronological position. O(n).
    void insert(const Reservation& reservation);

    // Remove by id. The removed record is copied into removedOut so the caller
    // (e.g. the cancellation stack) keeps it after the node is deleted.
    // Returns false when no reservation carries that id. O(n).
    bool remove(int reservationId, Reservation& removedOut);
    bool remove(int reservationId);

    // Traverse: walks the chain looking for an id. Returns nullptr when
    // absent. The pointer stays valid until that node is removed. O(n).
    Reservation*       find(int reservationId);
    const Reservation* find(int reservationId) const;

    // Traverse by position, 0-based. Lets other modules walk the records
    // without exposing Node. Returns false when index is out of range. O(n).
    bool getAt(int index, Reservation& out) const;

    // Traverse looking for a time clash on the same resource. ignoreId lets a
    // reservation skip itself when its own times are being changed. O(n).
    bool hasResourceConflict(const std::string& resourceId,
                             const std::string& date,
                             int startHour,
                             int endHour,
                             int ignoreId = -1) const;

    // Traverse looking for a clash in one student's own schedule. O(n).
    bool hasStudentConflict(const std::string& studentId,
                            const std::string& date,
                            int startHour,
                            int endHour,
                            int ignoreId = -1) const;

    // Traverse counting one student's bookings on a date. O(n).
    int countForStudent(const std::string& studentId,
                        const std::string& date) const;

    // ----- display -----
    void display() const;                                    // every record
    void displayForStudent(const std::string& studentId) const;
    void displayForResource(const std::string& resourceId) const;

    // ----- housekeeping -----
    int  size()    const;   // O(1), count is maintained on insert/remove
    bool isEmpty() const;
    void clear();           // O(n)
};

#endif // RESERVATIONLIST_H
