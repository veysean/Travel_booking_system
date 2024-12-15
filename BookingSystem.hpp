#ifndef BOOKINGSYSTEM_HPP
#define BOOKINGSYSTEM_HPP

#include "Customer.hpp"
#include "Hotel.hpp"

class BookingSystem
{
private:
    Customer *customers;
    Hotel *hotels;

public:
    //loading data from file
    void loadingFromFile()
    {

    }

    //save to file
    void saveDataToFile()
    {

    }

    //Create new account(sign up)
    void signUp()
    {

    }

    //login to the system
    void logIn()
    {

    }


    //Add hotel
    void addHotel()
    {

    }

    //remove hotel from the system
    void removeHotel(int hotelId)
    {


    }

    //display all hotels in the system
    void displayAllHotel()
    {

    }

    //display hotel by province
    void displayHotelByProvince(std::string location)
    {

    }

    //display hotel by name 
    void displayHotelByName(std::string name)
    {

    }
};

#endif