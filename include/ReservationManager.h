#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H
#include <string>
#include "Reservation.h"
#include "ResourceManager.h"

class ReservationManager{
private:
    struct Node
    {
        Reservation reservation;
        Node* next;

        Node(const Reservation& reservation, Node* next);
    };

    Node* head;

public:

    ReservationManager();

    ~ReservationManager();

    void InsertReservation(Reservation);

    bool RemoveReservation(int ReservationID, Reservation& RemovedReservation);

    void DisplayReservations() const;

    bool ReservationExists(int ReservationID) const;

    bool ValidateReservation(int ReservationID, string StudentName, int StudentID, string ResourceID, string ReservationDate, ResourceManager& resourceManager ) const;

};

#endif