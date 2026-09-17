//CancellationHistory header placeholder- samie
#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H
#include "Reservation.h" //pulls reservation class definatoon as our calss needs to know reservation  is to store

class CancellationHistory {
private:
	struct Node {
		Reservation data;
		Node* next;

		Node(Reservation r) : data(r), next(nullptr) {} // This is the Node's constructor: when you create a Node and pass it a Reservation (r),
        // it automatically stores that reservation in "data" and sets "next" to nullptr

	};
	Node* top;// Pointer to the Node currently on top of the stack (the most recently cancelled reservation)
	int count;

public:
	CancellationHistory();
	~CancellationHistory(); //Destructor declaration

	void pushCancellation(Reservation r);

	Reservation popAndRestore();

	bool isEmpty() const;
	int getCount() const;
	void displayHistory() const;

};
#endif//CancellationHistory header placeholder- samie
