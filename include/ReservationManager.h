#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H
#include <string>
#include "Reservation.h"
#include "ResourceManager.h"
#include "WaitingList.h"
#include "CancellationHistory.h"

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

    bool InsertReservation(Reservation reservation);

    bool RemoveReservation(int ReservationID, Reservation& RemovedReservation);

    void DisplayReservations() const;

    bool ReservationExists(int ReservationID) const;

    bool ValidateReservation(int ReservationID, string StudentName, int StudentID, string ResourceID, string ReservationDate, ResourceManager& resourceManager, const WaitingList& waitingList, const CancellationHistory& cancellationHistory ) const;

    const Reservation* SearchReservation(int ResrvationID) const;

    int CountReservationsforResource(const string& ResourceID) const;
};

#endif