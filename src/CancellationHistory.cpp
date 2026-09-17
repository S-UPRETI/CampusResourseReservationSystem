// CancellationHistory implementaion - samie
#include "CancellationHistory.h"
#include <iostream>
#include <stdexcept>

CancellationHistory::CancellationHistory() : top(nullptr), count(0) {}

CancellationHistory::~CancellationHistory() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

void CancellationHistory::pushCancellation(Reservation r) {
    Node* newNode = new Node(r);
    newNode->next = top;
    top = newNode;
    ++count;
}

Reservation CancellationHistory::popAndRestore() {
    if (isEmpty()) {
        throw std::runtime_error("Cancellation history is empty.");
    }

    Node* temp = top;

    Reservation restored = temp->data;
    top = top->next;
    delete temp;
    --count;
    return restored;
}

bool CancellationHistory::isEmpty() const {
    return top == nullptr;
}

int CancellationHistory::getCount() const {
    return count;
}

void CancellationHistory::displayHistory() const {
    if (isEmpty()) {
        std::cout << "Cancellation history is empty." << std::endl;
        return;
    }
    std::cout << "--- Cancellation History (most recent first) ---" << std::endl;
    const Node* current = top;
    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}
