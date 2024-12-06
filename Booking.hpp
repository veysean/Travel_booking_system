#ifndef BOOKING_HPP
#define BOOKING_HPP

#include <string>

using namespace std;

#include "Hotel.hpp"

class Booking
{
private:
    Hotel *hotels;
    // Date checkIn and checkout
    std::string checkIn;
    std::string checkOut;
    int duration;
    int bookingId;

public:
    Booking(std::string &checkIn, std::string &checkOut)
    {
        this->checkIn = checkIn;
        this->checkOut = checkOut;
        this->hotels = nullptr;
    }

    //loading data hotel from file
    void loadingDataHotel()
    {

    }

    //save Data hotel to file
    void saveDataHotel()
    {
        
    }
    
    // select hotel in order to booking by input Hotel ID
    void selectHotel(int hotelId)
    {
    }

    // check if the selected room whether available or not
    void isAvalaible(std::string checkIn, int duration, std::string roomType)
    {

        // show only available room based on checkin and duration

        // to increase the date(string)split string then convert to integer to increase, lastly concate string
    }
};

#endif