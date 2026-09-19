#include "ReservationManager.h"
#include <iostream>
using namespace std;

ReservationManager::Node::Node(const Reservation& reservation, Node* next):reservation(reservation), next (next){

}

ReservationManager::ReservationManager(){
    head=nullptr;

}

ReservationManager::~ReservationManager(){
    Node* current=head;
    while (current!=nullptr){
        Node* saved=current->next;
        delete current;
        current=saved;

    }

}

void ReservationManager::InsertReservation(Reservation reservation){
    if(ReservationExists(reservation.GetReservation_ID())){
        cout<<"Reservation ID already exists"<<endl;
        return;
    }

    Node* newNode= new Node(reservation, head);
    head= newNode;


}

bool ReservationManager::ReservationExists(int ReservationID) const{
    Node* current= head;
    while(current!=nullptr){
        if(current->reservation.GetReservation_ID()==ReservationID){
            return true;
        }

        current=current->next;
    }

    return false;
}

void ReservationManager::DisplayReservations() const{
    Node* current= head;
    while(current!=nullptr){
        current->reservation.display();
        current= current->next;

    }

}

bool ReservationManager::RemoveReservation(int ReservationID, Reservation& RemovedReservation){
    Node* current= head;
    Node* prev= nullptr;

    if (current==nullptr){
        cout<<"The reservation list is empty"<<endl;
        return false;

    }
    while (current!=nullptr){
        if(current->reservation.GetReservation_ID()!= ReservationID){
            prev=current;
            current=current->next;
        }
        else{
            if(head==current){
                RemovedReservation= current->reservation;
                head=current->next;
                delete current;
                return true;
            }
            else{
                RemovedReservation= current->reservation;
                prev->next=current->next;
                delete current;
                return true;
            }
        }
    }
    return false;
}


bool ReservationManager::ValidateReservation(int ReservationID, string StudentName, int StudentID, string ResourceID, string ReservationDate, ResourceManager& resourceManager) const{
    if(ReservationExists(ReservationID)){
        cout<<"Reservation ID invalid, reservation already exists"<<endl;
        return false;
    }

    Resource* resource = resourceManager.findResource (ResourceID);

    if (resource==nullptr){
        return false;

    };

    return true;
}