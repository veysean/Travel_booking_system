#ifndef BOOKING_HPP
#define BOOKING_HPP

#include <string>

class Booking
{
private:
    std::string customerName;
    int customerId;
    std::string checkIn;
    std::string Checkout;

public:
    Booking(std::string &customerName, int customerId, std::string &CheckIn, std::string &checkOut)
    {
        this->customerId = customerId;
        this->customerName = customerName;
        this->checkIn = checkIn;
        this->Checkout = checkOut;
    }
};

#endif