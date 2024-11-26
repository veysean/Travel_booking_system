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
    BookingSystem(/* args */);
    ~BookingSystem();
};



#endif