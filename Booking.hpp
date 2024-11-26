#ifndef BOOKING_HPP
#define BOOKING_HPP

#include <string>
#include<iostream>

#include "Hotel.hpp"

class Booking
{
private:
    Hotel *hotels;
    int bookId;
    // Date checkIn and checkout
    std::string checkIn;
    std::string checkOut;

public:
    Booking(std::string &checkIn, std::string &checkOut, int bookId)
    {
        this->checkIn = checkIn;
        this->checkOut = checkOut;
        this->bookId = bookId;
        this->hotels = nullptr;
    }
    //return booking id
    int getBookId()
    {
        return this->bookId;
    }
    //get booking checkin date
    std::string getCheckIn()
    {
        return this->checkIn;
    }
    //get booking checkout date
    std::string getCheckOut()
    {
        return this->checkOut;
    }
    void hotelInformation(int index){
        std::cout<<"Hotel Name : " + this->hotels->getHotelName();
        std::cout<<"Hotel Location : " + this->hotels->getLocation();
        this->hotels->roomInformation(index);
    }
};

#endif