// CancellationHistory implementaion - samie

#include "CancellationHistory.h"
#include <iostream>
#include <stdexcept>
using namespace std;

CancellationHistory::CancellationHistory()
    : top(nullptr), count(0) {
}

CancellationHistory::~CancellationHistory() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    count = 0;
}

void CancellationHistory::pushCancellation(Reservation r) {
    Node* newNode = new Node(r, top);

    top = newNode;
    count++;
}

Reservation CancellationHistory::popAndRestore() {
    if (isEmpty()) {
        throw runtime_error("Cancellation history is empty.");
    }

    Node* temp = top;
    Reservation restored = temp->data;

    top = top->next;

    delete temp;
    count--;

    return restored;
}

bool CancellationHistory::isEmpty() const {
    return top == nullptr;
}

int CancellationHistory::getCount() const {
    return count;
}

Reservation CancellationHistory::peek() const {
    if (isEmpty()) {
        throw runtime_error("Cancellation history is empty.");
    }

    return top->data;
}

bool CancellationHistory::containsReservationID(int reservationID) const {
    Node* current = top;

    while (current != nullptr) {
        if (current->data.GetReservation_ID() == reservationID) {
            return true;
        }

        current = current->next;
    }

    return false;
}

int CancellationHistory::countReservationsForResource(
    const string& resourceID) const {

    int resourceCount = 0;
    Node* current = top;

    while (current != nullptr) {
        if (current->data.GetResource_ID() == resourceID) {
            resourceCount++;
        }

        current = current->next;
    }

    return resourceCount;
}

void CancellationHistory::displayHistory() const {
    if (isEmpty()) {
        cout << "Cancellation history is empty." << endl;
        return;
    }

    cout << "--- Cancellation History (most recent first) ---"
         << endl;

    const Node* current = top;

    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}
