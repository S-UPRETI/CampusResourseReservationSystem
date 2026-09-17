//WaitingList class header- samie
// WaitingList implementation - samie
#ifndef WAITINGLIST_H
#define WAITINGLIST_H
#include "Reservation.h"

class WaitingList {
private:
    // A single node in the linked queue.
    struct Node {
        Reservation data;
        Node* next;
        Node(Reservation r) : data(r), next(nullptr) {}
    };

    Node* front;   
    Node* rear;   
    int count;     

public:
    // Constructor: initializes an empty waiting list.
    WaitingList();

    // Destructor: frees all remaining nodes to prevent memory leaks.
    ~WaitingList();

    // Adds a student's reservation request to the back of the queue.
    
    void addToWaitlist(Reservation r);


  
    Reservation removeFromWaitlist();

    // Returns true if no one is currently waiting.
    bool isEmpty() const;

  
    int getCount() const;

    void displayWaitlist() const;
};

#endif
