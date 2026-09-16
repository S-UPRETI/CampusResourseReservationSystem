#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H
#include <string>
#include "Reservation.h"

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

    bool RemoveReservation(int ReservationID);

    void DisplayReservations() const;

    bool ReservationExists(int ReservationID) const;

    bool ValidateReservation(int ReservationID, std::string StudentName, int StudentID, std::string ResourceID, std::string ReservationDate) const;

};

#endif