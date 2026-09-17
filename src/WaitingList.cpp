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
}

Reservation WaitingList::removeFromWaitlist() {
    if (isEmpty()) {
       
        throw runtime_error("Waiting list is empty.");
    }

    Node* temp = front;
    Reservation next = temp->data;
    front = front->next;   
    if (front == nullptr) {
       
        rear = nullptr;
    } delete temp;
    count--;

    return next; 
}
bool WaitingList::isEmpty() const {
    return front == nullptr;  

int WaitingList::getCount() const {
    return count;  

void WaitingList::displayWaitlist() const {
    if (isEmpty()) {
        cout << "Waiting list is empty." << endl;
        return;
    }
    Node* current = front;
    cout << "--- Waiting List (front to back) ---" << endl;
    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}
