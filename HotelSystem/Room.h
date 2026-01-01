#pragma once
#include <string>
#include <iostream>

class Room
{
public:
    Room() {}
    ~Room() {}

    Room(int number, std::string type, double price)
        : roomNumber(number), roomType(type), pricePerNight(price), isOccupied(false)
    {
    }

    // Getters
    int getRoomNumber() const { return roomNumber; }
    std::string getRoomType() const { return roomType; }
    double getPricePerNight() const { return pricePerNight; }
    bool getIsOccupied() const { return isOccupied; }

    // Setters
    void setRoomNumber(int number) { roomNumber = number; }
    void setRoomType(const std::string& type) { roomType = type; }
    void setPricePerNight(double price) { pricePerNight = price; }
    void setIsOccupied(bool occupied) { isOccupied = occupied; }

    void displayRoomInfo() const
    {
        std::cout << "Room Number: " << roomNumber << "\n";
        std::cout << "Room Type: " << roomType << "\n";
        std::cout << "Price Per Night: $" << pricePerNight << "\n";
        std::cout << "Occupied: " << (isOccupied ? "Yes" : "No") << "\n";
    }

private:
    int roomNumber;
    std::string roomType;
    double pricePerNight;
    bool isOccupied;
};