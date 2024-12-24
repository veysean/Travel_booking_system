#ifndef HOTEL_HPP
#define HOTEL_HPP

#include "Room.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory> // For std::unique_ptr

class Hotel
{
private:
    std::string name;
    std::string location;
    int hotelId;
    std::vector<std::unique_ptr<Room>> rooms;

public:
    Hotel(int hotelId, const std::string &name, const std::string &location)
    {
        this->hotelId = hotelId;
        this->name = name;
        this->location = location;
    }

    void loadingRoomData(int hotelId)
    {
        rooms.clear(); // Clear existing rooms before loading new data
        std::string filename = "ID" + std::to_string(hotelId) + "RoomList.txt";
        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "Fail to load data: " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream linestream(line);
            std::string roomId, roomPrice, roomType;
            if (std::getline(linestream, roomId, ',') &&
                std::getline(linestream, roomType, ',') &&
                std::getline(linestream, roomPrice))
            {
                int id = std::stoi(roomId);
                double price = std::stod(roomPrice);
                rooms.push_back(std::make_unique<Room>(id, price, roomType));
            }
        }
        file.close();
    }

    void saveRoomData(int hotelId)
    {
        std::string filename = "ID" + std::to_string(hotelId) + "RoomList.txt";
        std::ofstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "Fail to save data!" << std::endl;
            return;
        }
        for (const auto &room : rooms)
        {
            file << room->getId() << "," << room->getType() << "," << room->getPrice() << std::endl;
        }
        file.close();
    }

    void addRoom(int roomId, double price, const std::string &type)
    {
        rooms.push_back(std::make_unique<Room>(roomId, price, type));
    }

    void removeRoom(int index)
    {
        if (index < 0 || index >= rooms.size())
        {
            std::cout << "Invalid room index! Fail to remove." << std::endl;
            return;
        }
        rooms.erase(rooms.begin() + index);
        std::cout << "Remove Successful!" << std::endl;
    }

    void displayAllRoom()
    {
        if (rooms.empty())
        {
            std::cout << "No room data." << std::endl;
            return;
        }
        std::cout << "----------Room List----------" << std::endl;
        for (const auto &room : rooms)
        {
            room->displayRoomDetails();
        }
    }

    std::string getHotelName() const
    {
        return name;
    }

    std::string getHotelLocation() const
    {
        return location;
    }

    int getHotelId() const
    {
        return hotelId;
    }
};

#endif