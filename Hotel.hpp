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
    // hotel name
    std::string name;
    // hotel location
    std::string location;
    // hotel ID
    int hotelId;
    // room in hotel from room.hpp
    std::vector<std::unique_ptr<Room>> rooms;

public:
    Hotel(int &hotelId, const std::string &name, const std::string &location)
    {
        this->hotelId = hotelId;
        this->name = name;
        this->location = location;
    }

    // loading room data from file
    void loadingRoomData(int hotelId)
    {
        std::string filename = "ID" + std::to_string(hotelId) + "RoomList.txt";
        std::ifstream file(filename); // open the file as read mode

        if (!file.is_open())
        {
            std::cerr << "fail to load data!" << filename << std::endl;
            return;
        }

        std::string line; // line to store data form file line by line
        while (std::getline(file, line))
        {
            std::istringstream linestream(line);

            std::string roomId, roomPrice, roomType;
            if (std::getline(linestream, roomId, ',') &&
                std::getline(linestream, roomPrice, ',') &&
                std::getline(linestream, roomType))
            {

                int id = std::stoi(roomId);
                double price = std::stod(roomPrice);
                // Use std::make_unique to create unique_ptr and push it into the vector
                rooms.push_back(std::make_unique<Room>(id, roomType, price));
            }
        }
        file.close();
    }

    // save room data to file
    void saveRoomData(int hotelId)
    {
        std::string filename = "ID" + std::to_string(hotelId) + "RoomList.txt";
        std::ofstream file(filename); // open the file as write mode

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

    // add room in the hotel one by one
    void addRoom(int roomId, std::string &type, double price)
    {
        rooms.push_back(std::make_unique<Room>(roomId, type, price));
    }

    // remove room by index
    void removeRoom(int index)
    {
        if (index < 0 || index > rooms.size())
        {
            std::cout << "Invalid room index! fail to remove." << std::endl;
            return;
        }
        rooms.erase(rooms.begin() + index);
        std::cout << "Remove Successful!" << std::endl;
    }
    // display all the room information in the hotel
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
            room->roomDetail("ID" + std::to_string(hotelId) + "RoomList.txt");
        }
    }
    // return hotel name
    std::string getHotelName() const
    { // use const to ensure that the method Does not modify the object
        return name;
    }
    // return hotel location
    std::string getHotelLocation() const
    {
        return location;
    }
    // return hotel id
    int getHotelId() const
    {
        return hotelId;
    }
};

#endif