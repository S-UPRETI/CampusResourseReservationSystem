//CancellationHistory header placeholder- samie

#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include <string>
#include "Reservation.h"

class CancellationHistory {
private:
    struct Node {
        Reservation data;
        Node* next;
  Node(Reservation r, Node* nextNode)
            : data(r), next(nextNode) {}
    };

    Node* top;
int count;

public:
    CancellationHistory();
    ~CancellationHistory();

void pushCancellation(Reservation r);
Reservation popAndRestore();
 Reservation peek() const;

 bool isEmpty() const;
    int getCount() const;
  void displayHistory() const;

 // Check whether a reservation ID exists in cancellation history
    bool containsReservationID(int reservationID) const;
   // Count cancelled reservations for a particular resource
    int countReservationsForResource(
        const std::string& resourceID) const;
};

#endif
