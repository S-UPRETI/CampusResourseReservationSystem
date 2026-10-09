
#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <string>
#include "Reservation.h"

class WaitingList {
private:
    struct Node {
        Reservation data;
        Node* next;

        Node(Reservation r) : data(r), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    int count;

public:
    WaitingList();
    ~WaitingList();

    void addToWaitlist(Reservation r);
    Reservation removeFromWaitlist();

    bool isEmpty() const;
    int getCount() const;
    void displayWaitlist() const;
    Reservation peek() const;

    // Check whether a reservation ID is already waiting
 bool containsReservationID(int reservationID) const;
 // Count waiting reservations for a particular resource
  int countReservationsForResource(
        const std::string& resourceID) const;
 // Find the first waiting reservation for a resource without removing it
    bool peekFirstForResource(
    const std::string& resourceID,
       Reservation& foundReservation) const;

 // Remove a reservation by ID after it has been successfully promoted
    bool removeReservationID(int reservationID);

};

#endif
