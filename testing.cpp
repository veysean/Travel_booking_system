//++++++++++++++++++Test Hotel+++++++++++++++++++

#include "hotel.hpp"
#include "room.hpp"
#include <iostream>
int main()
{
    // Create a Hotel object
    Hotel myHotel(1, "krovan", "kompot");

    // Add rooms to the hotel
    myHotel.addRoom(101, 150.0, "1bed");
    myHotel.addRoom(102, 150.0, "1bed");
    myHotel.addRoom(103, 150.0, "1bed");
    myHotel.addRoom(104, 150.0, "1bed");
    myHotel.addRoom(105, 150.0, "1bed");
    myHotel.addRoom(106, 200.0, "2beds");
    myHotel.addRoom(107, 200.0, "2beds");
    myHotel.addRoom(108, 200.0, "2beds");
    myHotel.addRoom(109, 200.0, "2beds");
    myHotel.addRoom(110, 200.0, "2beds");

    // Save room data to file
    myHotel.saveRoomData(myHotel.getHotelId());

    // Display all rooms
    myHotel.displayAllRoom();

    // Remove a room
    myHotel.removeRoom(0);

    // Display all rooms after removal
    myHotel.displayAllRoom();

    // Load room data from file
    myHotel.loadingRoomData(myHotel.getHotelId());

    // Display all rooms after loading from file
    myHotel.displayAllRoom();

    return 0;
}


//++++++++++++++++++++++++Test Booking++++++++++++++++++++++++
// #include "booking.hpp"
// #include "customer.hpp"
// #include "hotel.hpp"
// #include "room.hpp"
// #include "DateUtils.hpp"
// #include <iostream>

// int main()
// {
//     // Create a Hotel object
//     Hotel myHotel(1, "Grand Hotel", "Downtown");

//     // Add rooms to the hotel
//     myHotel.addRoom(101, 150.0, "Single");
//     myHotel.addRoom(102, 200.0, "Double");

//     // Save room data to file
//     myHotel.saveRoomData(myHotel.getHotelId());

//     // Create a Booking object
//     Booking myBooking(1, myHotel.getHotelId(), myHotel.getHotelName(), "23-12-2024", "25-12-2024");

//     // Check room availability
//     myBooking.isAvailable(myHotel.getHotelId(), "23-12-2024", 2, "Single");

//     // Display booking details
//     std::cout << "Booking ID: " << myBooking.getBookingId() << std::endl;
//     std::cout << "Check-in Date: " << myBooking.getCheckIn() << std::endl;
//     std::cout << "Check-out Date: " << myBooking.getCheckOut() << std::endl;
//     std::cout << "Hotel ID: " << myBooking.getHotelId() << std::endl;
//     std::cout << "Hotel Name: " << myBooking.getHotelName() << std::endl;

//     // Create a Customer object
//     Customer myCustomer(1, "customer@example.com", "John Doe", "Male", "password123");

//     // Load bookings from file
//     myCustomer.loadBookingsFromFile();

//     // Add a booking
//     myCustomer.addBooking(myHotel.getHotelId());

//     // Display current bookings
//     myCustomer.displayCurrentBooking();

//     // Cancel a booking
//     //myCustomer.cancelBooking(1);

//     // Display current bookings after cancellation
//     myCustomer.displayCurrentBooking();

//     return 0;
// }

// #include <iostream>
// #include "Booking.hpp"
// #include "Customer.hpp"
// #include "DateUtils.hpp"

// int main()
// {
//     // Create a customer
//     Customer customer(1, "john.doe@example.com", "John Doe", "Male", "password123");

//     // Load existing bookings from file
//     customer.loadBookingsFromFile();

//     // Display current bookings
//     customer.displayCurrentBooking();

//     // Add a new booking
//     int hotelId = 1; // Example hotel ID
//     customer.addBooking(hotelId);

//     // Display updated bookings
//     customer.displayCurrentBooking();

//     // Cancel a booking
//     // int bookingIdToCancel = 1; // Example booking ID to cancel
//     // customer.cancelBooking(bookingIdToCancel);

//     // Display bookings after cancellation
//     //customer.displayCurrentBooking();

//     return 0;
// }