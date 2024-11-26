#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>

class Room
{
private:
    // 1 mean room is available and 0 room unavailable
    bool available;
    // price of the room
    double price;
    // typs of room like 1bed or 2beds
    std::string type;

public:
    // Constructor
    Room(double price, std::string &type)
    {
        this->price = price;
        this->type = type;
        this->available = 1;
    }

    // Check for availability of room
    bool isAvailable()
    {

        return available;
    }

    // display room info( price & type)
    void roomDetail()
    {
    }
};

#endif