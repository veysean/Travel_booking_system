#ifndef HOTEL_HPP
#define HOTELL_HPP

#include "Room.hpp"
#include "Booking.hpp"

#include <string>
#include <vector>

class Hotel
{
private:
    std::string name;
    std::string location;
    std::vector<Room> rooms;
    std::vector<Booking> bookings;

public:
};

#endif