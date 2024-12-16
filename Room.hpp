#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Room
{
private:
    // Unique room ID
    int roomID;
    // 1 mean room is available and 0 room unavailable
    bool available;
    // price of the room
    double price;
    // typs of room like 1bed or 2beds
    std::string roomType;

public:
    // Constructor
    Room(int roomID, double price, std::string &type)
    {   this->roomID = roomID;
        this->price = price;
        this->roomType = type;
        this->available = 1;   // Default to available
    }


    // display all rooms that available
    void isRoomAvailable()
    {

    }

    // display room info( price & type)
    void roomDetail(int roomID, double price, std::string &type)
    {
        
    }

   
};

#endif