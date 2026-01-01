#include "HotelManager.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    HotelManager manager;
    int choice;
    int roomNumber;
    string roomType;
    double roomPrice;
    string guestName;
    int nights;

    while (true)
    {
        cout << "\n=== HOTEL MANAGEMENT SYSTEM ===\n";
        cout << "1. Add Room\n";
        cout << "2. Show All Rooms\n";
        cout << "3. Book Room\n";
        cout << "4. Checkout Room\n";
        cout << "5. Show All Bookings\n";
        cout << "6. Calculate Total Revenue\n";
        cout << "0. Exit\n";
        cout << "Choose action: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cout << endl;

        switch (choice)
        {
        case 1:
            cout << "Enter room number: ";
            cin >> roomNumber;
            cout << "Enter room type (single/double/suite): ";
            cin >> roomType;
            cout << "Enter price per night: ";
            cin >> roomPrice;
            manager.addRoom(roomNumber, roomType, roomPrice);
            break;

        case 2:
            cout << "\n--- All Rooms ---\n";
            manager.showAllRooms();
            break;

        case 3:
            cout << "Enter room number to book: ";
            cin >> roomNumber;
            cout << "Enter guest name (use_underscores): ";
            cin.ignore();
            cin >> guestName; // Using cin for simplicity as per requirements
            cout << "Enter number of nights: ";
            cin >> nights;

            if (manager.bookRoom(roomNumber, guestName, nights)) {
                cout << "Room booked successfully!\n";
            }
            break;

        case 4:
            cout << "Enter room number to checkout: ";
            cin >> roomNumber;
            if (manager.checkOutRoom(roomNumber)) {
                // message is handled inside checkOutRoom
            }
            break;

        case 5:
            cout << "\n--- All Bookings ---\n";
            manager.showAllBookings();
            break;

        case 6:
            cout << "Total Revenue: $" << manager.calculateTotalRevenue() << "\n";
            break;

        case 0:
            cout << "Saving data and exiting...\n";
            return 0;

        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }
    }

    return 0;
}