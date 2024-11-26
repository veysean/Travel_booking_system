#ifndef CUSTOMER_HPP
#define CUSOTMER_HPP

#include <string>
#include<iostream>

#include "Booking.hpp"

class Customer
{
private:
    std::string customerName;
    std::string gender;
    int customerId;
    std::string phoneNumber;
    Booking *bookings;

public:
    Customer(std::string cutomerName, std::string gender, int customerId)
    {
        this->customerName = customerName;
        this->gender = gender;
        this->customerId = customerId;
        this->bookings = nullptr;
        this->phoneNumber = phoneNumber;
    }

    void addBooking()
    {
    }

    void cancelBooking()
    {
    }

    void displayBooking()
    {
        std::cout<<"-----Booking Detail"<<std::endl;
        std::cout<<"Traveler Information"<<std::endl;
        std::cout<<"Name : "<<this->customerName<<std::endl;
        std::cout<<"Phone Number : "<<this->phoneNumber<<std::endl;
        std::cout<<"-----Booking Information"<<std::endl;
        std::cout<<"Booking ID : "<<this->bookings->getBookId()<<std::endl;
        
        std::cout<<this->customerName;
    }
};

#endif