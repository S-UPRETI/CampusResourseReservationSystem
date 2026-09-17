// WaitingList implementation - samie
#ifndef WAITINGLIST_H
#define WAITINGLIST_H
#include "Reservation.h"

// QUEUE (FIFO - First In, First Out), implemented as a singly linked list.
// Used to manage students waiting for a resource that is currently unavailable.
// Kept separate from the active reservations linked list and the cancellation stack.
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