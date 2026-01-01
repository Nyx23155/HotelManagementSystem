#include "HotelManager.h"
#include <iostream>
#include <chrono>
#include <sstream>
#include <ctime>
#include <filesystem>
#include <iomanip> // Required for put_time

using namespace std;

HotelManager::HotelManager()
{
    ensureLogsDirectory();
    logFile = generateLogFilename();

    logingData("=== SYSTEM STARTED ===");

    // Attempt to load main data file on startup
    if (loadDataFromFile("hotel_data.txt")) {
        logingData("Data loaded successfully from hotel_data.txt");
    }
    else {
        logingData("No data file found. Starting with empty database.");
    }
}

HotelManager::~HotelManager()
{
    // Auto-save on exit
    saveDataToFile("hotel_data.txt");
    logingData("=== SYSTEM SHUTDOWN ===");
}

void HotelManager::addRoom(int number, const string& type, double price)
{
    // 1. Validate number (must be positive)
    if (number <= 0) {
        cout << "ERROR: Room number must be positive.\n";
        logingData("Failed to add room: Invalid number " + to_string(number));
        return;
    }

    // 2. Check for duplicates
    for (const auto& room : rooms) {
        if (room.getRoomNumber() == number) {
            cout << "ERROR: Room already exists.\n";
            logingData("Failed to add room " + to_string(number) + ": Already exists.");
            return;
        }
    }

    // 3. Validate price
    if (price <= 0) {
        cout << "ERROR: Price must be positive.\n";
        logingData("Failed to add room " + to_string(number) + ": Invalid price " + to_string(price));
        return;
    }

    // 4. Validate room type
    if (type != "single" && type != "double" && type != "suite") {
        cout << "ERROR: Invalid room type.\n";
        logingData("Failed to add room " + to_string(number) + ": Invalid type '" + type + "'");
        return;
    }

    Room newRoom(number, type, price);
    rooms.push_back(newRoom);
    cout << "Room added!\n";

    logingData("Created Room " + to_string(number) + " [" + type + "] Price: " + to_string(price));

    saveDataToFile("hotel_data.txt");
}

void HotelManager::showAllRooms() const
{
    for (const auto& room : rooms)
    {
        room.displayRoomInfo();
        cout << "-----------------------\n";
    }
}

Room* HotelManager::findRoomByNumber(int number)
{
    for (auto& room : rooms)
    {
        if (room.getRoomNumber() == number)
        {
            return &room;
        }
    }
    return nullptr;
}

bool HotelManager::bookRoom(int roomNumber, const string& guestName, int nights)
{
    Room* room = findRoomByNumber(roomNumber);

    // Validation: Check if room exists and is free
    if (room == nullptr) {
        cout << "Error: Room not found.\n";
        logingData("Booking failed: Room " + to_string(roomNumber) + " not found.");
        return false;
    }

    if (room->getIsOccupied()) {
        cout << "Error: Room is already occupied.\n";
        logingData("Booking failed: Room " + to_string(roomNumber) + " is already occupied.");
        return false;
    }

    double totalPrice = room->getPricePerNight() * nights;
    Booking newBooking(roomNumber, guestName, nights, totalPrice);
    bookings.push_back(newBooking);
    room->setIsOccupied(true);

    logingData("BOOKING SUCCESS: Room " + to_string(roomNumber) +
        " | Guest: " + guestName +
        " | Nights: " + to_string(nights) +
        " | Total: " + to_string(totalPrice));

    return true;
}

bool HotelManager::checkOutRoom(int roomNumber)
{
    Room* room = findRoomByNumber(roomNumber);

    if (room && room->getIsOccupied())
    {
        room->setIsOccupied(false);
        cout << "Checkout successful!\n";
        logingData("CHECKOUT: Room " + to_string(roomNumber) + " is now free.");
        return true;
    }
    else
    {
        cout << "Error: Room not found or not occupied.\n";
        logingData("Checkout failed for Room " + to_string(roomNumber) + ": Not occupied or invalid number.");
        return false;
    }
}

void HotelManager::showAllBookings() const
{
    for (const auto& booking : bookings)
    {
        booking.displayBookingInfo();
        cout << "-----------------------\n";
    }
}

double HotelManager::calculateTotalRevenue() const
{
    double totalRevenue = 0.0;
    for (const auto& booking : bookings)
    {
        totalRevenue += booking.getTotalPrice();
    }
    return totalRevenue;
}

void HotelManager::saveDataToFile(const string& filename) const
{
    string fullSavePath = "saves/" + filename;

    ofstream outFile(fullSavePath);
    if (!outFile) {
        logingData("ERROR: Failed to save data to " + filename);
        return;
    }

    // Format: "ROOMS" -> count -> list of rooms
    outFile << "ROOMS" << endl;
    outFile << rooms.size() << endl;
    for (const auto& room : rooms)
    {
        outFile << room.getRoomNumber() << " "
            << room.getRoomType() << " "
            << room.getPricePerNight() << " "
            << room.getIsOccupied() << endl;
    }

    // Format: "BOOKINGS" -> count -> list of bookings
    outFile << "BOOKINGS" << endl;
    outFile << bookings.size() << endl;
    for (const auto& booking : bookings)
    {
        outFile << booking.getRoomNumber() << " "
            << booking.getGuestName() << " "
            << booking.getNights() << " "
            << booking.getTotalPrice() << endl;
    }

    outFile.close();
}

bool HotelManager::loadDataFromFile(const string& filename)
{
    string fullSavePath = "saves/" + filename;
    ifstream inFile(fullSavePath);

    if (!inFile) return false;

    rooms.clear();
    bookings.clear();

    string header;
    int count;

    // Load Rooms Section
    inFile >> header;
    if (header != "ROOMS") return false; // Corrupted file or wrong format

    inFile >> count;
    for (int i = 0; i < count; ++i)
    {
        int number;
        string type;
        double price;
        bool occupied;

        inFile >> number >> type >> price >> occupied;

        Room room(number, type, price);
        room.setIsOccupied(occupied);
        rooms.push_back(room);
    }

    // Load Bookings Section (Optional)
    inFile >> header;
    if (header == "BOOKINGS")
    {
        inFile >> count;
        for (int i = 0; i < count; ++i)
        {
            int rNum;
            string gName;
            int nights;
            double total;

            inFile >> rNum >> gName >> nights >> total;
            Booking booking(rNum, gName, nights, total);
            bookings.push_back(booking);
        }
    }

    return true;
}

bool HotelManager::ensureLogsDirectory()
{
    // Create 'logs' and 'saves' folders if they don't exist
    try {
        if (!fs::exists("logs")) fs::create_directory("logs");
        if (!fs::exists("saves")) fs::create_directory("saves");
        return true;
    }
    catch (...) {
        return false;
    }
}

string HotelManager::generateLogFilename()
{
    // Log filename format: session-YYYY-MM-DD__HH-MM-SS.log
    return "session-" + getCurrentTimestampForFile() + ".log";
}

string HotelManager::getCurrentTimestampForFile()
{
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    struct tm tm;
    localtime_s(&tm, &time);

    stringstream ss;
    ss << put_time(&tm, "%Y-%m-%d__%H-%M-%S");
    return ss.str();
}

void HotelManager::logingData(const string& message) const
{
    string fullLogPath = "logs/" + logFile;
    ofstream logFile(fullLogPath, ios::app); // Append mode

    if (logFile.is_open()) {
        auto now = chrono::system_clock::now();
        time_t time = chrono::system_clock::to_time_t(now);
        struct tm tm;
        localtime_s(&tm, &time);

        logFile << "[" << put_time(&tm, "%H:%M:%S") << "] " << message << endl;
        logFile.close();
    }
}