#ifndef HOTEL_HPP
#define HOTEL_HPP

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

    // loading room data from file
    void loadingRoomData()
    {
    }

    // save room data to file
    void saveRoomData()
    {
    }

    // add room in the hotel one by one
    void addRoom(int roomId, double price, std::string type)
    {
        rooms.push_back(new Room(roomId, price, type));
    }

    // remove room by index
    void removeRoom(int index)
    {
    }

    // update hotel(modify)
    void updateHotel(int hotelId)
    {
    }
};

#endif