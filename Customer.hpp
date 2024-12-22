#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Booking.hpp"

class Customer
{
private:
    int customerId;
    std::string customerEmail;
    std::string customerName;
    std::string gender;
    std::string customerPassword;
    std::vector<Booking> bookings;

    bool isLeapYear(int year)
    {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    // function to check days and months
    int daysInMonth(int month, int year)
    {
        switch (month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
        }
    }
    // split date to day, month, year
    void splitdate(std::string &checkIn, std::string &day, std::string &month, std::string &year)
    {
        std::stringstream ss(checkIn);

        std::getline(ss, day, '-');
        std::getline(ss, month, '-');
        std::getline(ss, year);
    }
    // check check-in date
    bool checkCheckIn(std::string &checkIn)
    {
        std::string day, month, year;
        splitdate(checkIn, day, month, year);
        int checkInDay = stoi(day);
        int checkInMonth = stoi(month);
        int checkInYear = stoi(year);
        if (checkInDay > daysInMonth(checkInMonth, checkInYear))
        {
            return false;
        }
        if (checkInMonth > 12 || checkInMonth <= 0)
        {
            return false;
        }
        return true;
    }
    // calculate check-out date with stay duration
    std::string calculateCheckOutDate(std::string &checkIn, int duration)
    {
        std::string day;
        std::string month;
        std::string year;
        splitdate(checkIn, day, month, year);
        int checkOutDay = stoi(day) + duration - 1;
        int checkOutMonth = stoi(month);
        int checkOutYear = stoi(year);
        while (checkOutDay > daysInMonth(checkOutMonth, checkOutYear))
        {
            checkOutDay -= daysInMonth(checkOutMonth, checkOutYear);
            checkOutMonth++;
            if (checkOutMonth > 12)
            {
                checkOutMonth = 1;
                checkOutYear++;
            }
        }
        return (checkOutDay < 10 ? "0" : "") + std::to_string(checkOutDay) + "-" +
               (checkOutMonth < 10 ? "0" : "") + std::to_string(checkOutMonth) + "-" +
               std::to_string(checkOutYear);
    }

public:
    Customer(int customerId, std::string cutomerEmail, std::string customerName, std::string gender, std::string customerPassword)
    {
        this->customerId = customerId;
        this->customerEmail = customerEmail;
        this->customerName = customerName;
        this->gender = gender;
        this->customerPassword = customerPassword;
    }
    // read file and store in vector
    void loadBookingsFromFile()
    {
        int hotelId;
        std::ifstream file("ID" + std::to_string(customerId) + "UserBooking.txt");
        if (!file.is_open())
        {
            std::cout << "Unable opening booking file.\n";
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            int bookingId, hotelId;
            std::string hotelName, checkIn, checkOut;

            // Read data from the file
            ss >> bookingId;
            ss.ignore(); // Skip comma
            ss >> hotelId;
            ss.ignore();
            std::getline(ss, hotelName, ',');
            std::getline(ss, checkIn, ',');
            std::getline(ss, checkOut, ',');

            // Directly construct a Booking object in the vector using emplace_back
            bookings.emplace_back(bookingId, hotelId, hotelName, checkIn, checkOut);
        }

        file.close();
    }

    void addBooking(int hotelId)
    {
        // user input location and and choose hotel and input checkin and type of bed so the program will show the number of available room

        std::string checkIn;
        int duration;
        std::string roomType;
        int numOfRoom;
        int bookingId = bookings.size() + 1;
        std::string day, month, year;

        // user inputs check-in date
        bool validDate = false;
        do
        {
            std::cout << "Enter check-in date (DD-MM-YYYY): ";
            std::cin >> checkIn;

            if (checkCheckIn(checkIn))
            {
                validDate = true;
            }
            else
            {
                std::cout << "Invalid date entered. Please try again." << std::endl;
            }
        } while (!validDate);
        splitdate(checkIn, day, month, year);

        // user inputs duration and roomtype
        std::cout << "Enter duration (in days): ";
        std::cin >> duration;
        std::cout << "Enter room type (e.g., 1bed, 2beds): ";
        std::cin >> roomType;

        // call isAvailble to show the number of available rooms
        for (auto &booking : bookings)
        {
            booking.isAvalaible(hotelId, checkIn, duration, roomType);
        }

        std::cout << "Enter numbers of the rooms:";
        std::cin >> numOfRoom;
        std::string checkOut = calculateCheckOutDate(checkIn, duration);
    }

    void cancelBooking(int bookingId)
    {
        // ensure that bookings vector is empty
        bookings.clear();
        // load booking info from file
        loadBookingsFromFile();
        bool found = false;
        int hotelId;

        for (int i = 0; i < bookings.size(); ++i)
        {
            if (bookings[i].getBookingId() == bookingId)
            {
                found = true;
                bookings.erase(bookings.begin() + i);
                std::cout << "Booking with ID " << bookingId << "has been canceled." << std::endl;

                std::ofstream file("ID" + to_string(customerId) + "UserBooking.txt");
                if (!file.is_open())
                {
                    std::cout << "Unable to open the file." << std::endl;
                    return;
                }
                for (auto &booking : bookings)
                {
                    file << booking.getBookingId() << ","
                         << booking.getHotel()->getHotelId() << ","
                         << booking.getHotel()->getHotelName() << ","
                         << booking.getCheckIn() << ","
                         << booking.getCheckOut() << "," << std::endl;
                }
                file.close();

                std::ofstream hotelFile("ID" + std::to_string(hotelId) + "HotelBooking.txt");

                if (!hotelFile)
                {
                    std::cout << "Unable opening hotel file." << std::endl;
                    return;
                }

                // Write the remaining bookings to the hotel file
                for (auto &booking : bookings)
                {
                    hotelFile << booking.getBookingId() << ","
                              << booking.getHotel()->getHotelId() << ","
                              << booking.getHotel()->getHotelName() << ","
                              << booking.getCheckIn() << ","
                              << booking.getCheckOut() << std::endl;
                }

                // Close the hotel file
                hotelFile.close();
                return;
            }
        }
        if (!found)
        {
            std::cout << "Booking with ID " << bookingId << " was not found." << std::endl;
        }
    }

    // display all current bookings
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
        for (auto &booking : bookings)
        {
            std::cout << "Booking ID: " << booking.getBookingId() << std::endl
                      << "Hotel ID: " << booking.getHotel()->getHotelId() << std::endl
                      << "Hotel Name: " << booking.getHotel()->getHotelName() << std::endl
                      << "Check-in Date: " << booking.getCheckIn() << std::endl
                      << "Check-out Date: " << booking.getCheckOut() << std::endl
                      << "-------------------------------------------------" << std::endl;
        }
    }

    int getCustomerId()
    {
        return this->customerId;
    }
    std::string getCustomerEmail()
    {
        return this->customerEmail;
    }
    std::string getCustomerName()
    {
        return this->customerName;
    }
    std::string getGender()
    {
        return this->gender;
    }
    std::string getCustomerPassword()
    {
        return this->customerPassword;
    }
};

#endif;