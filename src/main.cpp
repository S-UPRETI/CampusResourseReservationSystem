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
        
        cout<<" Enter your choice: ";
        cin>>choice;

        switch(choice){

            case 1:// Display all resources
                
                break;

            case 2://Display available resources
                
                break;
            
            case 3://create reservation

                break;

            case 4://cancel reservation

                break;

            case 5://display active reservations

                break;

            case 6://display waiting list

                break;

            case 7://display cancellation history

                break;

            case 8://undo last cancellation

                break;

            case 9://exit
                cout<<"Exiting program..." << endl;
                break;

            default:// invalid choice
            
                break;



        }

    } while(choice!=9);

    return 0;

}
