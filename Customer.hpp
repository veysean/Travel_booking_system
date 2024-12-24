#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include "Booking.hpp"
#include "DateUtils.hpp"

class Customer
{
private:
    int customerId;
    std::string customerEmail;
    std::string customerName;
    std::string gender;
    std::string customerPassword;
    std::vector<Booking> bookings;

public:
    Customer(int customerId, const std::string &customerEmail, const std::string &customerName, const std::string &gender, const std::string &customerPassword)
        : customerId(customerId), customerEmail(customerEmail), customerName(customerName), gender(gender), customerPassword(customerPassword) {}

    // Read file and store in vector (File Customer booking)
    void loadBookingsFromFile()
    {
        std::string filename = "ID" + std::to_string(customerId) + "UserBooking.txt";
        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::ofstream newFile(filename);
            if (!newFile.is_open())
            {
                std::cerr << "Unable to create file: " << filename << std::endl;
                return;
            }
            std::cout << "File created: " << filename << std::endl;
            newFile.close();
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            int bookingId, hotelId;
            std::string hotelName, checkIn, checkOut;

            ss >> bookingId;
            ss.ignore();
            ss >> hotelId;
            ss.ignore();
            std::getline(ss, hotelName, ',');
            std::getline(ss, checkIn, ',');
            std::getline(ss, checkOut, ',');

            bookings.emplace_back(bookingId, hotelId, hotelName, checkIn, checkOut);
        }

        file.close();
    }

    void addBooking(int hotelId)
    {
        std::string checkIn;
        int duration;
        std::string roomType;
        int numOfRoom;

        std::cout << "Enter check-in date (DD-MM-YYYY): ";
        std::cin >> checkIn;
        std::cout << "Enter duration (in days): ";
        std::cin >> duration;
        std::cout << "Enter room type (e.g., Single, Double): ";
        std::cin >> roomType;

        bool roomAvailable = false;
        for (auto &booking : bookings)
        {
            booking.isAvailable(hotelId, checkIn, duration, roomType);
            if (booking.isAvailable(hotelId, checkIn, duration, roomType))
            {
                roomAvailable = true;
                break;
            }
        }

        if (roomAvailable)
        {
            std::cout << "Enter number of rooms: ";
            std::cin >> numOfRoom;
            std::string checkOut = DateUtils::calculateCheckOutDate(checkIn, duration);

            int bookingId = bookings.size() + 1;
            Booking newBooking(bookingId, hotelId, "Hotel Name", checkIn, checkOut); // Replace "Hotel Name" with actual hotel name
            bookings.push_back(std::move(newBooking));

            std::ofstream file("ID" + std::to_string(customerId) + "UserBooking.txt", std::ios::app);
            if (file.is_open())
            {
                file << bookingId << "," << hotelId << "," << "hotel Name" << "," << checkIn << "," << checkOut << "\n"; // Replace "Hotel Name" with actual hotel name
                file.close();
            }
            else
            {
                std::cerr << "Unable to open file for writing: ID" << customerId << "UserBooking.txt" << std::endl;
            }

            // Save to HotelBooking file
            bookings.back().saveToHotelBookingFile(hotelId);
        }
        else
        {
            std::cout << "No rooms available for the selected dates and room type." << std::endl;
        }
    }


    void cancelBooking(int bookingId)
    {
        bookings.clear();
        loadBookingsFromFile();
        bool found = false;

        for (size_t i = 0; i < bookings.size(); ++i)
        {
            if (bookings[i].getBookingId() == bookingId)
            {
                found = true;
                int hotelId = bookings[i].getHotelId();
                bookings.erase(bookings.begin() + i);
                std::cout << "Booking with ID " << bookingId << " has been canceled." << std::endl;

                std::ofstream file("ID" + std::to_string(customerId) + "UserBooking.txt");
                if (!file.is_open())
                {
                    std::cout << "Unable to open the file." << std::endl;
                    return;
                }
                for (const auto &booking : bookings)
                {
                    file << booking.getBookingId() << ","
                         << booking.getHotelId() << ","
                         << booking.getHotelName() << ","
                         << booking.getCheckIn() << ","
                         << booking.getCheckOut() << "\n";
                }
                file.close();

                std::ofstream hotelFile("ID" + std::to_string(hotelId) + "HotelBooking.txt");
                if (!hotelFile.is_open())
                {
                    std::cout << "Unable to open hotel file." << std::endl;
                    return;
                }

                for (const auto &booking : bookings)
                {
                    hotelFile << booking.getBookingId() << ","
                              << booking.getHotelId() << ","
                              << booking.getHotelName() << ","
                              << booking.getCheckIn() << ","
                              << booking.getCheckOut() << "\n";
                }
                hotelFile.close();
                return;
            }
        }
        if (!found)
        {
            std::cout << "Booking with ID " << bookingId << " was not found." << std::endl;
        }
    }

    // Display all current bookings
    void displayCurrentBooking()
    {
        bookings.clear();
        loadBookingsFromFile();

        if (bookings.empty())
        {
            std::cout << "No bookings available." << std::endl;
            return;
        }

        std::cout << "Displaying all bookings: " << std::endl;
        for (const auto &booking : bookings)
        {
            std::cout << "Booking ID: " << booking.getBookingId() << std::endl
                      << "Hotel ID: " << booking.getHotelId() << std::endl
                      << "Hotel Name: " << booking.getHotelName() << std::endl
                      << "Check-in Date: " << booking.getCheckIn() << std::endl
                      << "Check-out Date: " << booking.getCheckOut() << std::endl
                      << "-------------------------------------------------" << std::endl;
        }
    }

    int getCustomerId() const { return customerId; }
    std::string getCustomerEmail() const { return customerEmail; }
    std::string getCustomerName() const { return customerName; }
    std::string getCustomerGender() const { return gender; }
    std::string getCustomerPassword() const { return customerPassword; }
};

#endif