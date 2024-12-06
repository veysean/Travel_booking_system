#ifndef BOOKING_HPP
#define BOOKING_HPP

#include <string>

#include "Hotel.hpp"

class Booking
{
private:
    Hotel *hotels;
    // Date checkIn and checkout
    std::string checkIn;
    std::string checkOut;

public:
    Booking(std::string &checkIn, std::string &checkOut)
    {
        this->checkIn = checkIn;
        this->checkOut = checkOut;
        this->hotels = nullptr;
    }
};

#endif