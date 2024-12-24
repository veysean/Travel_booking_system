#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Room
{
private:
    int roomID;
    std::string roomType;
    double price;

public:
    Room(int roomID, double price, const std::string &type)
    {
        this->roomID = roomID;
        this->price = price;
        this->roomType = type;
    }

    void displayRoomDetails() const
    {
        std::cout << "Room ID: " << roomID << ", Price: $" << price << ", Room Type: " << roomType << std::endl;
    }

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

                displayRoomDetails();
            }
            else
            {
                std::cerr << "Error: Invalid data format in file." << "\n";
            }
        }

        file.close();
    }

    int getId() const
    {
        return roomID;
    }

    std::string getType() const
    {
        return roomType;
    }

    double getPrice() const
    {
        return price;
    }
};

#endif