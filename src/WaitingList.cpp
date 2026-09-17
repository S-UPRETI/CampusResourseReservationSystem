#include "WaitingList.h"
#include <iostream>
#include <stdexcept>
using namespace std;

WaitingList::WaitingList() {
    front = nullptr;   // empty queue: nothing at the front
    rear = nullptr;    // empty queue: nothing at the rear
    count = 0;
}

WaitingList::~WaitingList() {
    // Walk the linked list and delete each node manually,
    // since we allocated them with "new" ourselves.
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
}

void WaitingList::addToWaitlist(Reservation r) {
    Node* newNode = new Node(r);

    if (isEmpty()) {
        // Special case: queue is empty, so the new node is both
        // the front and the rear.
        front = newNode;
        rear = newNode;
    } else {
        // Normal case: attach the new node after the current rear,
        // then move rear forward to point at it.
        rear->next = newNode;
        rear = newNode;
    }
    count++;

    // O(1): whether empty or not, this never loops through the queue.
    // This is exactly why we keep a rear pointer instead of relying
    // solely on front - without it, adding to the end would require
    // traversing the whole list (O(n)) every time.
}

Reservation WaitingList::removeFromWaitlist() {
    if (isEmpty()) {
        // Reservation has no default constructor, so we can't return
        // a blank object. We throw instead - caller must check
        // isEmpty() before calling this.
        throw runtime_error("Waiting list is empty.");
    }

    Node* temp = front;
    Reservation next = temp->data;
    front = front->next;   // move front forward to the next-longest-waiting student

    if (front == nullptr) {
        // We just removed the last node in the queue, so rear
        // must also be reset to nullptr - otherwise it would be
        // left pointing at deleted memory (a dangling pointer).
        rear = nullptr;
    }

    delete temp;
    count--;

    return next;

    // O(1): pointer reassignment only, no shifting of remaining elements.
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