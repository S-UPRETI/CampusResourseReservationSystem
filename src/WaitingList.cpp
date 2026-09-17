#include "WaitingList.h"
#include <iostream>
#include <stdexcept>
using namespace std;

WaitingList::WaitingList() {
    front = nullptr;   // empty queue nothing at the front
    rear = nullptr;    // empty queue nothing at the rear
    count = 0;
}

WaitingList::~WaitingList() {
  
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
}

void WaitingList::addToWaitlist(Reservation r) {
    Node* newNode = new Node(r);

    if (isEmpty()) {
      
        front = newNode;
        rear = newNode;
    } else {
        
        rear->next = newNode;
        rear = newNode;
    }
    count++;

Reservation WaitingList::removeFromWaitlist() {
    if (isEmpty()) {
       
        throw runtime_error("Waiting list is empty.");
    }

    Node* temp = front;
    Reservation next = temp->data;
    front = front->next;   // move front forward to the next-longest-waiting student

    if (front == nullptr) {
       
        rear = nullptr;
    }

    delete temp;
    count--;

    return next;

  
}

bool WaitingList::isEmpty() const {
    return front == nullptr;   // O(1)
}

int WaitingList::getCount() const {
    return count;   // O(1): stored value, not recalculated by traversal
}

void WaitingList::displayWaitlist() const {
    if (isEmpty()) {
        cout << "Waiting list is empty." << endl;
        return;
    }

    // Must visit every node once, front to back - O(n),
    // unlike add/remove which are O(1).
    Node* current = front;
    cout << "--- Waiting List (front to back) ---" << endl;
    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}
