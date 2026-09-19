#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>
using namespace std;

class Reservation{
private:
    int ReservationID;
    int StudentID;
    string StudentName;
    string ResourceID;
    string ReservationDate;

public:
    
    Reservation();
    Reservation(int Reservation_ID, int Student_ID, string Student_Name, string Resource_ID, string Reservation_Date);

    int GetReservation_ID() const;
    int GetStudent_ID() const;
    string GetStudent_Name() const;
    string GetResource_ID() const;
    string GetReservation_Date() const;
    void display() const;




};

#endif
