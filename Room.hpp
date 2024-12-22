#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <fstream>
#include <sstream>

class Room
{
private:
    // 1 mean room is available and 0 room unavailable
    bool available;
    // price of the room
    double price;
    // typs of room like 1bed or 2beds
    std::string roomType;
    



public:
    // Constructor
    Room(double price, std::string &type)
    {
        this->price = price;
        this->roomType = type;
        this->available = 1;
    }

    // check if room is available
    void isRoomAvailable(std::string &hotel,std::string &roomNum,std::string &type,int checkInDay, int checkInMonth, int checkInYear, int numberOfDays)
    {
        
    }

    // display room info( price & type)
    void roomDetail(std::string &hotel, std::string &roomNum)
    {  
    }
};

#endif