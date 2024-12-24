#ifndef BOOKING_HPP
#define BOOKING_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include "Hotel.hpp"
#include "DateUtils.hpp"

class Booking
{
private:
    std::vector<Hotel> hotels;
    std::string checkIn;
    std::string checkOut;
    int bookingId;
    int hotelId;
    std::string roomType;
    std::string hotelName;

public:
    Booking(int bookingId, int hotelId, const std::string &hotelName, const std::string roomType, const std::string &checkIn, const std::string &checkOut)
        : bookingId(bookingId), hotelId(hotelId), hotelName(hotelName), checkIn(checkIn), checkOut(checkOut) {}

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

    bool isAvailable(int hotelId, const std::string &checkIn, int duration, const std::string &roomType)
    {
        std::string requestedCheckOut;
        try
        {
            requestedCheckOut = DateUtils::isValidDateAndIncrement(checkIn, duration);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid date or duration: " << e.what() << std::endl;
            return false;
        }

        std::string filename = "ID" + std::to_string(hotelId) + "HotelBooking.txt";
        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "File does not exist. Assuming room is available." << std::endl;
            return true; // Room is available if no booking file exists
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::vector<std::string> parts = split(line, ',');
            if (parts.size() < 6)
            {
                std::cerr << "Skipping malformed line in file: " << line << std::endl;
                continue;
            }

            std::string fileRoomType = parts[3];
            std::string fileCheckIn = parts[4];
            std::string fileCheckOut = parts[5];

            // Check for overlapping dates and matching room type
            if (fileRoomType == roomType && !(checkIn >= fileCheckOut || requestedCheckOut <= fileCheckIn))
            {
                std::cerr << "Room not available for requested dates." << std::endl;
                return false;
            }
        }

        std::cout << "Room is available for requested dates." << std::endl;
        return true;
    }

    void saveToHotelBookingFile(int hotelId,std::string roomType)
    {
        std::string filename = "ID" + std::to_string(hotelId) + "HotelBooking.txt";
        std::ofstream file(filename, std::ios::app);

        if (!file.is_open())
        {
            std::cerr << "Unable to open file: " << filename << std::endl;
            return;
        }

        file << bookingId << "," << hotelId << "," << hotelName << "," << roomType << "," << checkIn << "," << checkOut << "\n";
        file.close();
    }

    int getBookingId() const { return bookingId; }
    std::string getCheckIn() const { return checkIn; }
    std::string getCheckOut() const { return checkOut; }
    int getHotelId() const { return hotelId; }
    std::string getHotelName() const { return hotelName; }
    std::string getRoomType() const { return roomType; }
};

#endif