#ifndef BOOKING_HPP
#define BOOKING_HPP

#include <string>

using namespace std;

#include "Hotel.hpp"

class Booking
{
private:
    int bookingId;
    Hotel *hotels;
    // Date checkIn and checkout
    std::string checkIn;
    std::string checkOut;
    int duration;

public:
    Booking(int bookingId, std::string &checkIn, std::string &checkOut)
    {
        this->bookingId = bookingId;
        this->checkIn = checkIn;
        this->checkOut = checkOut;
        hotels = nullptr;

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
    static void isAvalaible()
    {

        // show only available room based on checkin and duration

        // to increase the date(string)split string then convert to integer to increase, lastly concate string
    }
    static void displayBookingDetails()
    {

    }
    int getBookingId(){
        return bookingId;
    }
    std::string getCheckIn(){
        return checkIn;
    }
    std::string getCheckOut(){
        return checkOut;
    }
    Hotel* getHotel(){
        return hotels;
    }
};

#endif;