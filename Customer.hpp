#ifndef CUSTOMER_HPP
#define CUSOTMER_HPP

#include <string>

#include "Booking.hpp"

class Customer
{
private:
    std::string customerName;
    std::string gender;
    int customerId;
    Booking *bookings;

public:
    Customer(std::string cutomerName, std::string gender, int customerId)
    {
        this->customerName = customerName;
        this->gender = gender;
        this->customerId = customerId;
        this->bookings = nullptr;
    }

    void addBooking()
    {
    }

    void cancelBooking()
    {
    }

    void displayBooking()
    {
    }
};

#endif