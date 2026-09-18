//CancellationHistory header placeholder- samie
#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H
#include "Reservation.h" //pulls reservation class definatoon as our calss needs to know reservation  is to store

class CancellationHistory {
private:
	struct Node {
		Reservation data;
		Node* next;
// to store a reservation and connect it to the next node
	Node(Reservation r, Node* nextNode) : data(r), next(nextNode) {} 
	};
	Node* top;
	int count;

public:
	CancellationHistory();
	~CancellationHistory(); 
// function for adding restoring checking displaying cancellation 
void pushCancellation(Reservation r);

Reservation popAndRestore();

bool isEmpty() const;
int getCount() const;
void displayHistory() const;
};
#endif
