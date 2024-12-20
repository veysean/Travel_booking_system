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
    // types of room like 1bed or 2beds
    std::string roomType;
    //price of the room
    double price;

public:
    // Constructor
    Room(int roomID, double price, std::string &type)
    {   this->roomID = roomID;
        this->price = price;
        this->roomType = type;
    }
    
    // Default constructor
    Room() : roomID(0), price(0.0), roomType("") {}

    // Display room info (price & type)
    void displayRoomDetails()
    {
        std::cout << "Room ID: " << roomID << ", Price: $" << price << ", Room Type: " << roomType <<std::endl;
    }

    // display room info( price & type) read from file
    void roomDetail(const std::string &filename)
    {
        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "Error: Unable to open file " << filename << "\n";
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            int id;
            std::string type;
            double cost;

            if (iss >> id >> type >> cost)
            {
                roomID = id;
                roomType = type;
                price = cost;

                // Display the room details
                displayRoomDetails();
            }
            else
            {
                std::cerr << "Error: Invalid data format in file." << "\n";
            }
        }

        file.close();

    }

   
};

#endif