// CancellationHistory implementaion - samie
#include "CancellationHistory.h"
#include <iostream>
#include <stdexcept>
using namespace std;
//this starts with an empty stack
CancellationHistory::CancellationHistory() : top(nullptr), count(0) {}

//to delete all the nodes after they are destroyred 
CancellationHistory::~CancellationHistory() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

//add a cancelled reservation to the top of the atacxk 
void CancellationHistory::pushCancellation(Reservation r) {
    Node* newNode = new Node(r,top );
  
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
    cout << "Cancellation history is empty." <<endl;
    return;
}
   cout << "--- Cancellation History (most recent first) ---" << endl;
    const Node* current = top;
    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}
