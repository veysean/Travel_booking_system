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
    Hotel(int& hotelId,const std::string& name,const std::string& location)
    {
        this->hotelId = hotelId;
        this->name = name;
        this->location = location;
    }


    //loading room data from file
    void loadingRoomData()
    {

    }

    //save room data to file
    void saveRoomData()
    {
        
    }

    // add room in the hotel one by one
    void addRoom(double price, std::string type)
    {
        rooms.push_back(new Room(price, type));
    }

    // remove room by index
    void removeRoom(int index)
    {
         if(index < 0 || index > rooms.size()){
            std::cout<<"Invalid room index! fail to remove."<<std::endl;
            return;
        }
        rooms.erase(rooms.begin() + index);
        std::cout<<"Remove Successful!"<<std::endl;
    }
    //display all the room information in the hotel
    void displayAllRoom(){
        if(rooms.empty()){
            std::cout<<"No room data."<<std::endl;
            return;
        }
        std::cout<<"----------Room List----------"<<std::endl;
        for(const auto& room : rooms){
            room->roomDetail();
        }

    }
    //return hotel name
    std::string getHotelName() const{//use const to ensure that the method Does not modify the object
        return name;
    }
    //return hotel location 
    std::string getHotelLocation() const{
        return location;
    }
    //return hotel id
    int getHotelId() const{
        return hotelId;
    }

    

};

#endif