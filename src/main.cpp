#include "ResourceManager.h"
#include "ReservationManager.h"
#include "WaitingList.h"
#include "CancellationHistory.h"

#include <iostream>
#include <limits>
#include <string>

using namespace std;

// Reads non-empty text.
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

// Reads an integer and handles invalid input.
int readInt(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;

        if (cin >> value) {
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            return value;
        }

        cout << "Please enter a valid number.\n";

        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );
    }
}

// Reports active reservations and waiting students for each resource.
void displayResourceUtilization(
    const ResourceManager& resources,
    const ReservationManager& reservations,
    const WaitingList& waitingList
) {
    cout << "\n=== RESOURCE UTILIZATION ===\n";

    cout << "Resource ID | Resource Name"
         << "         | Active reservations"
         << " | Waiting students\n";

    cout << "------------------------------------------------"
         << "--------------------------\n";

    for (const Resource& resource : resources.getAllResources()) {
        cout << resource.getResourceID()
             << "       | "
             << resource.getName();

        int spaces =
            22 - static_cast<int>(resource.getName().size());

        for (int i = 0; i < spaces; ++i) {
            cout << ' ';
        }

        cout << "| "
             << reservations.CountReservationsforResource(
                    resource.getResourceID()
                )
             << "                   | "
             << waitingList.countReservationsForResource(
                    resource.getResourceID()
                )
             << '\n';
    }

    cout << "\nActive reservations are counted from "
         << "the active reservation linked list.\n";
}

// Reports the number of students waiting for each resource.
void displayWaitingStatistics(
    const ResourceManager& resources,
    const WaitingList& waitingList
) {
    cout << "\n=== WAITING-LIST STATISTICS ===\n";

    cout << "Resource ID | Resource Name"
         << "         | Students waiting\n";

    cout << "-------------------------------------------------------\n";

    for (const Resource& resource : resources.getAllResources()) {
        cout << resource.getResourceID()
             << "       | "
             << resource.getName();

        int spaces =
            22 - static_cast<int>(resource.getName().size());

        for (int i = 0; i < spaces; ++i) {
            cout << ' ';
        }

        cout << "| "
             << waitingList.countReservationsForResource(
                    resource.getResourceID()
                )
             << '\n';
    }

    cout << "Total students waiting: "
         << waitingList.getCount() << '\n';
}

int main() {
    CancellationHistory cancellationHistory;
    WaitingList waitingList;
    ResourceManager resourceManager;
    ReservationManager reservationManager;

    // Load resource information from the data file.
    if (!resourceManager.loadFromFile("data/resources.txt")) {
        cout << "Resources could not be loaded. "
             << "Check data/resources.txt.\n";

        return 1;
    }

    int choice = 0;

    do {
        cout << "\n===== Campus Resource Reservation System =====\n"
             << "1. Display all resources\n"
             << "2. Display available resources\n"
             << "3. Create reservation\n"
             << "4. Cancel reservation\n"
             << "5. Display active reservations\n"
             << "6. Display waiting list\n"
             << "7. Display cancellation history\n"
             << "8. Undo last cancellation\n"
             << "9. Search resource by ID (Linear Search)\n"
             << "10. Sort resources by name (Merge Sort)\n"
             << "11. Resource utilization report\n"
             << "12. Most requested resources report\n"
             << "13. Waiting-list statistics report\n"
             << "14. Search active reservations by ID\n"
             << "15. Exit\n";

        choice = readInt("Enter your choice: ");

        switch (choice) {
        case 1:
            resourceManager.displayAll();
            break;

        case 2:
            resourceManager.displayAvailable();
            break;

        case 3: {
            int reservationID =
                readInt("Reservation ID: ");

            int studentID =
                readInt("Student ID: ");

            string studentName =
                readText("Student name: ");

            string resourceID =
                readText("Resource ID: ");

            string reservationDate =
                readText("Reservation date: ");

            if (!resourceManager.findResource(resourceID)) {
                cout << "Resource ID not found. "
                     << "Reservation was not created.\n";
                break;
            }

            if (!reservationManager.ValidateReservation(
                    reservationID,
                    studentName,
                    studentID,
                    resourceID,
                    reservationDate,
                    resourceManager,
                    waitingList,
                    cancellationHistory
                )) {
                cout << "Reservation could not be created.\n";
                break;
            }

            Reservation reservation(
                reservationID,
                studentID,
                studentName,
                resourceID,
                reservationDate
            );


            Resource* resource =
                resourceManager.findResource(resourceID);

            if (resource->isAvailable()) {
                if (reservationManager.InsertReservation(reservation)){
                
                    resourceManager.setResourceAvailability(
                    resourceID, false
                );
                cout << "Reservation added to active reservations.\n";
                resourceManager.recordRequest(resourceID);

                } else{
                    cout<<"Reservation was not created"<<endl;
                }

            } else {
                waitingList.addToWaitlist(reservation);
                resourceManager.recordRequest(resourceID); // Counts valid requests added to waitlist
                
                cout << "Resource is unavailable; "
                     << "reservation added to waiting list.\n";
            }
            
            break;
        }

        case 4: {
            int reservationID =
                readInt("Reservation ID to cancel: ");

            Reservation removed;

            if (!reservationManager.RemoveReservation(
                    reservationID, removed
                )) {
                cout << "No active reservation with that ID "
                     << "was found.\n";
                break;
            }

            cancellationHistory.pushCancellation(removed);

            string resourceID = removed.GetResource_ID();

            resourceManager.setResourceAvailability(
                resourceID, true
            );

            Reservation promoted;

            if (waitingList.peekFirstForResource(
                    resourceID, promoted
                )) {

                if (reservationManager.InsertReservation(promoted)) {

                    waitingList.removeReservationID(
                        promoted.GetReservation_ID()
                    );

                    resourceManager.setResourceAvailability(
                        resourceID, false
                    );

                    cout << "Promoted a waiting reservation for "
                         << resourceID << ".\n";
                } 
                else{
                    cout<<"Waiting reservation could not be promoted"<<endl;
                }
            }

            cout << "Reservation cancelled and saved "
                 << "in cancellation history.\n";

            break;
        }

        case 5:
            reservationManager.DisplayReservations();
            break;

        case 6:
            waitingList.displayWaitlist();
            break;

        case 7:
            cancellationHistory.displayHistory();
            break;

        case 8: {
            if (cancellationHistory.isEmpty()) {
                cout << "There are no cancellations to undo.\n";
                break;
            }

            Reservation restored =
                cancellationHistory.popAndRestore();

            Resource* resource =
                resourceManager.findResource(
                    restored.GetResource_ID()
                );

            if (resource && resource->isAvailable()) {
                reservationManager.InsertReservation(restored);

                resourceManager.setResourceAvailability(
                    restored.GetResource_ID(), false
                );

                cout << "Reservation restored "
                     << "to active reservations.\n";
            } else {
                waitingList.addToWaitlist(restored);

                cout << "Resource is unavailable; restored "
                     << "reservation placed in waiting list.\n";
            }

            break;
        }

        case 9: {
            string resourceID =
                readText("Enter resource ID to search for: ");

            // Calls our own Linear Search implementation.
            Resource* result =
                resourceManager.findResource(resourceID);

            if (result) {
                cout << "Resource found using Linear Search:\n";

                cout << "ID: "
                     << result->getResourceID()
                     << " | Name: "
                     << result->getName()
                     << " | Type: "
                     << result->getType()
                     << " | Status: "
                     << (result->isAvailable()
                             ? "Available"
                             : "Unavailable")
                     << " | Requests: "
                     << result->getRequestCount()
                     << '\n';
            } else {
                cout << "No resource found with ID "
                     << resourceID << ".\n";
            }

            break;
        }

        case 10:
            // Calls our own Merge Sort implementation.
            resourceManager.sortResourcesByName();

            cout << "Resources sorted alphabetically "
                 << "using Merge Sort.\n";

            resourceManager.displayAll();
            break;

        case 11:
            displayResourceUtilization(
                resourceManager,
                reservationManager,
                waitingList
            );
            break;

        case 12:
            resourceManager.displayMostRequestedResources();
            break;

        case 13:
            displayWaitingStatistics(
                resourceManager,
                waitingList
            );
            break;
        
        case 14:{
            int reservationID= readInt("Enter reservation ID to search: ");

            const Reservation* outcome= reservationManager.SearchReservation(reservationID);

            if (outcome!=nullptr){
                outcome->display();
            }
            else{
                cout<<"No active reservation matches that ID"<<endl;
            }

            break;
        };

        case 15:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice. Please select 1-15.\n";
            break;
        }

    } while (choice != 15);

    return 0;
}
