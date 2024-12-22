#ifndef HOTEL_HPP
#define HOTELL_HPP

#include "Room.hpp"

#include <string>
#include <vector>

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
    std::vector<Room *> rooms;

public:
    Hotel(std::string &name, std::string &location, int hotelId)
    {
        this->name = name;
        this->location = location;
        this->hotelId = hotelId;
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
    void removeRoom(vector<Room>& rooms, int index)
    {
         if(index < 0 || index > rooms.size()){
            cout<<"Invalid room index! fail to remove."<<endl;
            return;
        }
        rooms.erase(rooms.begin() + index);
        cout<<"Remove Successful!"<<endl;
    }

    //update hotel(modify)
    void updateHotel(vector<Hotel>& hotels,int hotelId,const string& newName,const std::string& newLocation)
    {
        for(auto& hotel : hotels){
            if(hotel.hotelId == hotelId){
                //update detail
                hotel.name = newName;
                hotel.location = newLocation;
                cout<<"Update Successful!"<<endl;
                return;
            }
        }
        cout<<"Hotel with ID : "<<hotelId<<" not found"<<endl;

    }
    int getHotelId(){
        return hotelId;
    }
    std::string getHotelName(){
        return name;
    }
};

#endif