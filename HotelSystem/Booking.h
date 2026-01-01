#pragma once
#include <iostream>
#include <string>

class Booking
{
public:
    Booking() {}
    ~Booking() {}

    Booking(int room, std::string name, int nights, double cost)
        : roomNumber(room), guestName(name), nights(nights), totalPrice(cost)
    {
    }

    // Getters
    int getRoomNumber() const { return roomNumber; }
    std::string getGuestName() const { return guestName; }
    int getNights() const { return nights; }
    double getTotalPrice() const { return totalPrice; }

    // Setters
    void setRoomNumber(int room) { roomNumber = room; }
    void setGuestName(const std::string& firstName, const std::string& lastName) { guestName = firstName + "_" + lastName; }
    void setNights(int n) { nights = n; }
    void setTotalPrice(double price) { totalPrice = price; }

    void displayBookingInfo() const
    {
        std::cout << "Booking Information:\n";
        std::cout << "Room Number: " << roomNumber << "\n";
        std::cout << "Guest Name: " << guestName << "\n";
        std::cout << "Nights: " << nights << "\n";
        std::cout << "Total Price: $" << totalPrice << "\n";
    }

private:
    int roomNumber;
    std::string guestName;
    int nights;
    double totalPrice;
};