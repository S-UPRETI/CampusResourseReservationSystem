#include "Reservation.h"
#include <iostream>
using namespace std;


Reservation::Reservation(){
    ReservationID= 0;
    StudentID= 0;
    StudentName= "";
    ResourceID= "";
    ReservationDate= "";


}

Reservation::Reservation(int Reservation_ID, int Student_ID, string Student_Name, string Resource_ID, string Reservation_Date){
    ReservationID= Reservation_ID;
    StudentID= Student_ID;
    StudentName= Student_Name;
    ResourceID= Resource_ID;
    ReservationDate= Reservation_Date;


}

int Reservation::GetReservation_ID() const{

    return ReservationID;

}

int Reservation::GetStudent_ID() const{

    return StudentID;
}

string Reservation::GetStudent_Name() const{

    return StudentName;
}

string Reservation::GetResource_ID() const{

    return ResourceID;
}

string Reservation::GetReservation_Date() const{

    return ReservationDate;
}

void Reservation::display() const{

    cout<<"Reservation ID: "<<ReservationID<<endl;
    cout<<"Student ID: "<<StudentID<<endl;
    cout<<"Student Name: "<<StudentName<<endl;
    cout<<"Resource ID: "<<ResourceID<<endl;
    cout<<"Reservation Date: "<<ReservationDate<<endl;

}
