#ifndef BOOKING_HPP
#define BOOKING_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

using namespace std;

#include "Hotel.hpp"

class Booking
{
private:
    vector<Hotel> hotels;
    // Date checkIn and checkout
    std::string checkIn;
    std::string checkOut;
    int duration;
    int bookingId;

public:
    Booking(std::string &checkIn, std::string &checkOut)
    {
        this->checkIn = checkIn;
        this->checkOut = checkOut;
    }

    // loading data hotel from file or // Function to read hotels from a file
    

    // select hotel in order to booking by input Hotel ID
    int selectHotel(int hotelId)
    {
        vector<Hotel> hotels;
        string line;
        int hotelId;
        std::fstream fileHotel("hotelInfo.txt");
        if (!fileHotel.is_open())
        {
            std::cerr << "Unable to open file" << std::endl;
            return;
        }
        while (std::getline(fileHotel, line))
        {
            std::vector<std::string> parts = split(line, ',');
            int id = std::stoi(parts[0]);
            std::string name = parts[1];
            std::string location = parts[2];
            if (id == hotelId)
            {
                hotels.emplace_back(name, location, id);
                break;
            }
        }
        fileHotel.close();
        return hotelId;
    }
    // Function to check if a hotel meets the criteria
    // Function to select hotels based on user preferences

    // Helper function to split a string by a delimiter
    std::vector<std::string> split(const std::string &str, char delimiter)
    {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delimiter))
        {
            tokens.push_back(token);
        }
        return tokens;
    }
    // Helper function to increment a date string (format: DD-MM-YYYY)
    std::string incrementDate(const std::string &date, int days)
    {
        std::vector<std::string> parts = split(date, '-');
        int day = std::stoi(parts[0]);
        int month = std::stoi(parts[1]);
        int year = std::stoi(parts[2]);

        // Simple date increment logic (not accounting for month/year overflow)
        day += days;
        if (day > 30)
        { // Simplified logic assuming all months have 30 days
            day -= 30;
            month += 1;
            if (month > 12)
            {
                month = 1;
                year += 1;
            }
        }
        // Reconstruct the date string
        std::ostringstream newDate;
        newDate << (day < 10 ? "0" : "") << day << "-" << (month < 10 ? "0" : "") << month << "-" << year;
        return newDate.str();
    }

    // Helper function to validate a date string (format: DD-MM-YYYY)
    std::string isValidDateAndIncrement(const std::string &date, int days)
    {
        // Regular expression to match the date format DD-MM-YYYY
        std::regex datePattern(R"(\b(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-\d{4}\b)");

        if (!std::regex_match(date, datePattern))
        {
            throw std::invalid_argument("Invalid date format");
        }

        // Split the date into day, month, and year
        std::vector<std::string> parts = split(date, '-');
        int day = std::stoi(parts[0]);
        int month = std::stoi(parts[1]);
        int year = std::stoi(parts[2]);

        // Check if the day is valid for the given month
        if (month == 2)
        { // February
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (isLeapYear && day > 29)
                throw std::invalid_argument("Invalid date");
            if (!isLeapYear && day > 28)
                throw std::invalid_argument("Invalid date");
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
        { // April, June, September, November
            if (day > 30)
                throw std::invalid_argument("Invalid date");
        }
        else
        { // January, March, May, July, August, October, December
            if (day > 31)
                throw std::invalid_argument("Invalid date");
        }

        // Days in each month
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // Adjust for leap year
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeapYear)
        {
            daysInMonth[1] = 29; // February has 29 days in a leap year
        }

        // Increment the date
        day += days;
        while (day > daysInMonth[month - 1])
        {
            day -= daysInMonth[month - 1];
            month += 1;
            if (month > 12)
            {
                month = 1;
                year += 1;
                // Adjust for leap year in the new year
                isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
                daysInMonth[1] = isLeapYear ? 29 : 28;
            }
        }

        // Reconstruct the date string
        std::ostringstream newDate;
        newDate << (day < 10 ? "0" : "") << day << "-" << (month < 10 ? "0" : "") << month << "-" << year;
        return newDate.str();
    }

    // check if the selected room whether available or not
    bool isAvalaible(int hotelId, std::string checkIn, int duration, std::string roomType)
    {
        try
        {
            std::string requestedCheckOut = isValidDateAndIncrement(checkIn, duration);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << e.what() << std::endl;
            return false;
        }

        // show only available room based on checkin and duration
        // to increase the date(string)split string then convert to integer to increase, lastly concate string
        std::ifstream file("ID" + to_string(selectHotel(hotelId)) + "HotelBooking.txt");
        std::string line;
        bool available = false;

        if (!file.is_open())
        {
            std::cerr << "Unable to open file" << std::endl;
            return;
        }

        while (std::getline(file, line))
        {
            std::vector<std::string> parts = split(line, ',');
            std::string fileRoomType = parts[3];
            std::string fileCheckIn = parts[4];
            std::string fileCheckOut = parts[5];

            std::string requestedCheckOut = incrementDate(checkIn, duration);

            if (fileRoomType == roomType && (checkIn >= fileCheckOut || requestedCheckOut <= fileCheckIn))
            {
                available = true;
                break;
            }
        }

        file.close();

        if (available)
        {
            std::cout << "Room type " << roomType << " is available." << std::endl;
        }
        else
        {
            std::cout << "Room type " << roomType << " is not available." << std::endl;
        }
    }
};

#endif