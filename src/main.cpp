#include "ResourceManager.h"
#include "ReservationManager.h"
#include "WaitingList.h"
#include "CancellationHistory.h"
#include <iostream>
#include <string>

using namespace std;
// Asks the user to type some textand keeps asking if they leave it blank
string readText(const string& prompt) {
    string value;
  while (true) {
      cout << prompt;
    getline(cin, value);
     if (!value.empty()) {
            return value;
        }
cout << "This field cannot be empty.\n";
    }
}

// Asks the user to type a number and keeps asking if they type something wrong
int readInt(const string& prompt) {
  int value;
 while (true) {
  cout << prompt;
     if (cin >> value) {
      cin.ignore(); // clears leftover Enter key press
      return value;
        }
     cout << "Please enter a valid number.\n";
      cin.clear();
     cin.ignore(10000, '\n');
    }
}

int main(){

    CancellationHistory cancellationHistory;
    WaitingList waitingList;
    ResourceManager resourceManager;
    ReservationManager reservationManager;

        
    if (!resourceManager.loadFromFile("data/resources.txt")){
        cout<<"Resources could not be loaded"<<endl;
        return 1;
    }

    //menu

    int choice;

    do{

        cout<< "\n===== Campus Resource Reservation System ====="<<endl;
        cout<<"1. Display all resources"<< endl;
        cout<<"2. Display available resources"<<endl;
        cout<<"3. Create reservation"<< endl;
        cout<<"4. Cancel reservation"<< endl;
        cout<<"5. Display active reservations"<< endl;
        cout<<"6. Display waiting list"<< endl;
        cout<<"7. Display cancellation history"<<endl;
        cout<<"8. Undo last cancellation"<< endl;
        cout<<"9. Exit"<< endl;
        
        choice=readInt("Enter your choice");
       

        switch(choice){

            case 1:// Display all resources
                resourceManager.displayAll();
                break;

            case 2://Display available resources
                resourceManager.displayAvailable();
                break;
            
            case 3://create reservation
            {
            int ReservationID;
            int StudentID;
            string StudentName;
            string ResourceID;
            string ReservationDate;

            ReservationID= readInt("What is the Reservation ID? ");
            StudentID= readInt("What is the Student ID? ");
            StudentName= readText("What is the Student Name? ");
            ResourceID= readText("What is the Resource ID? ");
            ReservationDate= readText("What is the Reservation Date? ");

            if(!reservationManager.ValidateReservation(ReservationID,StudentName,StudentID,ResourceID,ReservationDate,resourceManager)){
                cout<<"Invalid Reservation ID or Resource ID"<<endl;
            }
            else{
                Reservation reservation(ReservationID,StudentID,StudentName,ResourceID, ReservationDate);
                Resource* resource= resourceManager.findResource(ResourceID);
                if(resource->isAvailable()){
                    reservationManager.InsertReservation(reservation);
                    resourceManager.setResourceAvailability(ResourceID,false);
                }
                else{       
                    waitingList.addToWaitlist(reservation);
                }

            }

                break;
            }

            case 4://cancel reservation
        {
            int ReservationID;
            Reservation removedReservation;

            ReservationID=readInt("Enter the Reservation ID of the reservation you would like to cancel: ");

            if(!reservationManager.RemoveReservation(ReservationID,removedReservation)){
                cout<<"Reservation cancellation was unsuccessful, reservation ID does not exist"<<endl;
            }
            else{

                cancellationHistory.pushCancellation(removedReservation);
                resourceManager.setResourceAvailability(removedReservation.GetResource_ID(),true);

                if(!waitingList.isEmpty()){
                    Reservation frontReservation=waitingList.peek();
                    if (frontReservation.GetResource_ID()==removedReservation.GetResource_ID()){
                        Reservation boostedReservation=waitingList.removeFromWaitlist();
                        reservationManager.InsertReservation(boostedReservation);
                        resourceManager.setResourceAvailability(boostedReservation.GetResource_ID(),false);
                    }
                }
            }
            break;
        }

                

            case 5://display active reservations
            reservationManager.DisplayReservations();
                break;

            case 6://display waiting list
 waitingList.displayWaitlist();
                break;

            case 7://display cancellation history
 cancellationHistory.displayHistory();
                break;

            case 8://undo last cancellation
{
    if (cancellationHistory.isEmpty()) {
        cout << "There is no cancellations to undo." << endl;
    } else {
        Reservation restored = cancellationHistory.popAndRestore();
        Resource* resource = resourceManager.findResource(restored.GetResource_ID());

        if (resource != nullptr && resource->isAvailable()) {

        reservationManager.InsertReservation(restored);
        resourceManager.setResourceAvailability(restored.GetResource_ID(), false);
        cout << "Restored to active reservations: ";
            restored.display();
    } else {
            waitingList.addToWaitlist(restored);
            cout << "resource no longer available. Restored reservation placed back in the waiting list: ";
            restored.display();
        }
    }
     break;
}

            case 9://exit
                cout<<"Exiting program..." << endl;
                break;

            default:// invalid choice
             cout << "Invalid choice. Please select 1-9." << endl;
                break;



        }

    } while(choice!=9);

    return 0;

}
