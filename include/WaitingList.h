//WaitingList class header- samie
// WaitingList implementation - samie
#ifndef WAITINGLIST_H
#define WAITINGLIST_H
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
};

#endif
