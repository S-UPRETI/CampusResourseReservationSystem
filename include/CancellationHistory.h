//CancellationHistory header placeholder- samie
#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H
#include "Reservation.h" //pulls reservation class definatoon as our calss needs to know reservation  is to store

class CancellationHistory {
private:
	struct Node {
		Reservation data;
		Node* next;

		Node(Reservation r) : data(r), next(nullptr) {} 
	};
	Node* top;
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
#endif
