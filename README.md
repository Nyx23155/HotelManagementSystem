# 🏨 Hotel Management System (C++)

A console-based application for managing hotel room bookings, developed in C++ using Object-Oriented Programming (OOP) principles.

## 📝 Description
This project simulates a hotel management system where users can manage rooms, book guests, check out, and calculate revenue. The system features a custom file-based database to save data between sessions and a logging system to track all operations.

## ✨ Features
* **Room Management**: Add new rooms with validation (Single/Double/Suite).
* **Booking System**: Book rooms for guests, automatically calculating the total cost based on nights and room type.
* **Checkout**: Process guest checkouts and free up rooms.
* **Data Persistence**: All data (rooms and bookings) is automatically saved to `saves/hotel_data.txt` and loaded on startup.
* **Logging System**: detailed logs of all actions and errors are saved in the `logs/` directory with timestamps.
* **Revenue Calculation**: View total earnings from all bookings.

## 🛠️ Technical Details
* **Language**: C++
* **Paradigm**: OOP (Classes, Encapsulation)
* **File I/O**: Custom text-based database format.
* **Architecture**: Separated into header (`.h`) and implementation (`.cpp`) files.

## 🚀 How to Run
1.  Clone the repository.
2.  Open the project in **Visual Studio**.
3.  Build and Run (Ctrl + F5).
4.  The application will automatically create `logs/` and `saves/` directories.

## 📂 Project Structure
* `main.cpp` - Entry point and menu loop.
* `HotelManager` - Core logic controller (facade).
* `Room` - Class representing a hotel room.
* `Booking` - Class representing a reservation.

---
*Created for educational purposes.*
