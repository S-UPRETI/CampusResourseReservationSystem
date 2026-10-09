
#include "WaitingList.h"
#include <iostream>
#include <stdexcept>
using namespace std;

WaitingList::WaitingList() {
    front = nullptr;
    rear = nullptr;
    count = 0;
}

WaitingList::~WaitingList() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }

    rear = nullptr;
    count = 0;
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
    Reservation nextReservation = temp->data;

    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    count--;

    return nextReservation;
}

bool WaitingList::isEmpty() const {
    return front == nullptr;
}

int WaitingList::getCount() const {
    return count;
}

void WaitingList::displayWaitlist() const {
    if (isEmpty()) {
        cout << "Waiting list is empty." << endl;
        return;
    }

    cout << "--- Waiting List (front to back) ---" << endl;

    Node* current = front;

    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}

Reservation WaitingList::peek() const {
    if (isEmpty()) {
        throw runtime_error("Waiting list is empty.");
    }

    return front->data;
}

bool WaitingList::containsReservationID(int reservationID) const {
    Node* current = front;

    while (current != nullptr) {
        if (current->data.GetReservation_ID() == reservationID) {
            return true;
        }

        current = current->next;
    }

    return false;
}

int WaitingList::countReservationsForResource(
    const string& resourceID) const {

    int resourceCount = 0;
    Node* current = front;

    while (current != nullptr) {
        if (current->data.GetResource_ID() == resourceID) {
            resourceCount++;
        }

        current = current->next;
    }

    return resourceCount;
}

bool WaitingList::peekFirstForResource(
    const string& resourceID,
    Reservation& foundReservation) const {

    Node* current = front;

    while (current != nullptr) {
        if (current->data.GetResource_ID() == resourceID) {
            foundReservation = current->data;
            return true;
        }

        current = current->next;
    }

    return false;
}

bool WaitingList::removeReservationID(int reservationID) {
    Node* current = front;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data.GetReservation_ID() == reservationID) {

            if (previous == nullptr) {
                front = current->next;
            } else {
                previous->next = current->next;
            }

            if (current == rear) {
                rear = previous;
            }

            delete current;
            count--;

            if (front == nullptr) {
                rear = nullptr;
            }

            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}
