#pragma once
#include "Room.h"
#include "Booking.h"
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>

// Use 'fs' alias for filesystem
namespace fs = std::filesystem;

class HotelManager
{
public:
    HotelManager();
    ~HotelManager();

    // Constructor with filename (optional usage)
    HotelManager(const std::string& filename)
    {
        ensureLogsDirectory();
        logFile = generateLogFilename();

        if (loadDataFromFile(filename)) {
            std::cout << "System initialized. Data loaded.\n";
        }
        else {
            std::cout << "System initialized. Starting with empty database.\n";
        }
    }

    // Room Management
    void addRoom(int number, const std::string& type, double price);
    void showAllRooms() const;
    Room* findRoomByNumber(int number);

    // Booking Management
    bool bookRoom(int roomNumber, const std::string& guestName, int nights);
    bool checkOutRoom(int roomNumber);
    void showAllBookings() const;
    double calculateTotalRevenue() const;

    // File I/O
    void saveDataToFile(const std::string& filename) const;
    bool loadDataFromFile(const std::string& filename);

    // Logging & Utilities
    void logingData(const std::string& message) const;
    std::string generateLogFilename();
    std::string getCurrentTimestampForFile();

private:
    std::vector<Room> rooms;
    std::vector<Booking> bookings;
    std::string dataFile;
    std::string logFile;
    bool ensureLogsDirectory();
};