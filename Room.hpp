#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>

class Room
{
private:
    int roomNumber;
    double price;
    std::string type;

public:
    Room(int roomNumber, double price, std::string &type)
    {
        this->price = price;
        this->roomNumber = roomNumber;
        this->type = type;
    }
};

#endif