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

bool ReservationManager::InsertReservation(Reservation reservation){
    if(ReservationExists(reservation.GetReservation_ID())){
        cout<<"Reservation ID already exists"<<endl;
        return false;
    }

    Node* newNode= new Node(reservation, head);
    head= newNode;
    return true;


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


bool ReservationManager::ValidateReservation(int ReservationID, string StudentName, int StudentID, string ResourceID, string ReservationDate, ResourceManager& resourceManager,  const WaitingList& waitingList, const CancellationHistory& cancellationHistory ) const{
    if(ReservationExists(ReservationID)||waitingList.containsReservationID(ReservationID)||cancellationHistory.containsReservationID(ReservationID)){
        cout<<"Reservation ID invalid, reservation already exists"<<endl;
        return false;
    }

    Resource* resource = resourceManager.findResource (ResourceID);

    if (resource==nullptr){
        cout<<"Resource ID does not exist"<<endl;
        return false;

    }

    return true;

}

const Reservation* ReservationManager::SearchReservation(int ReservationID) const{
    Node* current = head;

    while (current!=nullptr){
        if(current->reservation.GetReservation_ID()!= ReservationID){
            current=current->next;
        }
        else{
                return &current->reservation;
        }
    }
    return nullptr;
}

int ReservationManager::CountReservationsforResource(const string& ResourceID) const{

    Node* current=head;
    int count=0;

    while (current!=nullptr){
        if(current->reservation.GetResource_ID()== ResourceID){
            count+=1;
        }
        
        current=current->next;
    }
    return count;

}