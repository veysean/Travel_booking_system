#ifndef HOTEL_HPP
#define HOTELL_HPP

#include "Room.hpp"

#include <string>
#include <vector>

class Hotel
{
private:
    // hotel name
    std::string name;
    // hotel location
    std::string location;
    // hotel ID
    int hotelId;
    // room in hotel from room.hpp
    std::vector<Room *> rooms;

public:
    Hotel(std::string &name, std::string &location, int hotelId)
    {
        this->name = name;
        this->location = location;
        this->hotelId = hotelId;
    }

    // add room in the hotel one by one
    void addRoom(double price, std::string type)
    {
        rooms.push_back(new Room(price, type));
    }

    // remove room by index
    void removeRoom(int index)
    {
    }
};

#endif