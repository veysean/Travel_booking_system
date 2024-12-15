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
        std::cout << "Room ID: " << roomID
                  << ", Room Type: " << roomType
                  << ", Price: " << price << std::endl;
    }

    //getter
    int getRoomID() const 
    {
        return roomID;
    }

    double getPrice()
    {
        return price;
    }

    std::string getRoomType(const std::string &newType)
    {
        roomType = newType;
    }

    // Static method to load room data from a file
    static Room loadFromFile(std::ifstream &file)
    {
        int roomID;
        double price;
        std::string roomType;
        std::string line;

        // Assuming each line contains: RoomID,RoomType,Price,Available
        if (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string token;

            // Parse the line
            std::getline(iss, token, ',');
            roomID = std::stoi(token);

            std::getline(iss, token, ',');
            roomType = token;

            std::getline(iss, token, ',');
            price = std::stod(token);
        }
    }
};

#endif