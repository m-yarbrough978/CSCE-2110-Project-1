#include "ReservationList.h"
#include <iostream>

ReservationList::ReservationList() : head(nullptr), count(0) {
}

ReservationList::ReservationList(const ReservationList& other)
    : head(nullptr), count(0) {
    // Deep copy, keeping the original order. Appending with a tail pointer
    // avoids re-walking the list for every node, so this is O(n) overall.
    Node* tail = nullptr;
    for (Node* cur = other.head; cur != nullptr; cur = cur->next) {
        Node* copy = new Node(cur->data);
        if (tail == nullptr) {
            head = copy;
        } else {
            tail->next = copy;
        }
        tail = copy;
        count++;
    }
}

ReservationList& ReservationList::operator=(const ReservationList& other) {
    if (this == &other) return *this;

    clear();

    Node* tail = nullptr;
    for (Node* cur = other.head; cur != nullptr; cur = cur->next) {
        Node* copy = new Node(cur->data);
        if (tail == nullptr) {
            head = copy;
        } else {
            tail->next = copy;
        }
        tail = copy;
        count++;
    }
    return *this;
}

ReservationList::~ReservationList() {
    clear();
}

bool ReservationList::isBefore(const Reservation& a, const Reservation& b) {
    if (a.getDate() != b.getDate())           return a.getDate() < b.getDate();
    if (a.getStartHour() != b.getStartHour()) return a.getStartHour() < b.getStartHour();
    return a.getReservationId() < b.getReservationId();
}

void ReservationList::insert(const Reservation& reservation) {
    Node* fresh = new Node(reservation);

    // Empty list, or the new record sorts ahead of the current first record.
    if (head == nullptr || isBefore(reservation, head->data)) {
        fresh->next = head;
        head = fresh;
        count++;
        return;
    }

    // Walk until the next record sorts after the new one, then splice in.
    Node* cur = head;
    while (cur->next != nullptr && !isBefore(reservation, cur->next->data)) {
        cur = cur->next;
    }
    fresh->next = cur->next;
    cur->next = fresh;
    count++;
}

bool ReservationList::remove(int reservationId, Reservation& removedOut) {
    Node* prev = nullptr;
    Node* cur  = head;

    while (cur != nullptr && cur->data.getReservationId() != reservationId) {
        prev = cur;
        cur  = cur->next;
    }

    if (cur == nullptr) return false;   // id not in the list

    if (prev == nullptr) {
        head = cur->next;               // removing the first node
    } else {
        prev->next = cur->next;         // unlink a middle or last node
    }

    removedOut = cur->data;             // copy out before the node dies
    delete cur;
    count--;
    return true;
}

bool ReservationList::remove(int reservationId) {
    Reservation discarded;
    return remove(reservationId, discarded);
}

Reservation* ReservationList::find(int reservationId) {
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data.getReservationId() == reservationId) {
            return &(cur->data);
        }
    }
    return nullptr;
}

const Reservation* ReservationList::find(int reservationId) const {
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data.getReservationId() == reservationId) {
            return &(cur->data);
        }
    }
    return nullptr;
}

bool ReservationList::getAt(int index, Reservation& out) const {
    if (index < 0 || index >= count) return false;

    Node* cur = head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    out = cur->data;
    return true;
}

bool ReservationList::hasResourceConflict(const std::string& resourceId,
                                          const std::string& date,
                                          int startHour,
                                          int endHour,
                                          int ignoreId) const {
    Reservation probe(-1, "", resourceId, date, startHour, endHour);
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data.getReservationId() == ignoreId) continue;
        if (cur->data.overlapsWith(probe)) return true;
    }
    return false;
}

bool ReservationList::hasStudentConflict(const std::string& studentId,
                                         const std::string& date,
                                         int startHour,
                                         int endHour,
                                         int ignoreId) const {
    Reservation probe(-1, studentId, "", date, startHour, endHour);
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data.getReservationId() == ignoreId) continue;
        if (cur->data.conflictsForStudent(probe)) return true;
    }
    return false;
}

int ReservationList::countForStudent(const std::string& studentId,
                                     const std::string& date) const {
    int total = 0;
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data.getStudentId() == studentId && cur->data.getDate() == date) {
            total++;
        }
    }
    return total;
}

void ReservationList::display() const {
    if (head == nullptr) {
        std::cout << "  (no active reservations)" << std::endl;
        return;
    }
    std::cout << "  " << Reservation::header() << std::endl;
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        std::cout << "  " << cur->data.toString() << std::endl;
    }
    std::cout << "  " << count << " active reservation(s)." << std::endl;
}

void ReservationList::displayForStudent(const std::string& studentId) const {
    bool any = false;
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data.getStudentId() != studentId) continue;
        if (!any) {
            std::cout << "  " << Reservation::header() << std::endl;
            any = true;
        }
        std::cout << "  " << cur->data.toString() << std::endl;
    }
    if (!any) {
        std::cout << "  (no active reservations for " << studentId << ")" << std::endl;
    }
}

void ReservationList::displayForResource(const std::string& resourceId) const {
    bool any = false;
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data.getResourceId() != resourceId) continue;
        if (!any) {
            std::cout << "  " << Reservation::header() << std::endl;
            any = true;
        }
        std::cout << "  " << cur->data.toString() << std::endl;
    }
    if (!any) {
        std::cout << "  (no active reservations for " << resourceId << ")" << std::endl;
    }
}

int  ReservationList::size()    const { return count; }
bool ReservationList::isEmpty() const { return head == nullptr; }

void ReservationList::clear() {
    while (head != nullptr) {
        Node* doomed = head;
        head = head->next;
        delete doomed;
    }
    count = 0;
}
