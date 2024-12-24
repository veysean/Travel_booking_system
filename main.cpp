#include <iostream>
#include "BookingSystem.hpp"

int main()
{
    int choice;
    int loginOption;
    int searchOption;
    int hotelId;
    int bookingId;
    std::string province;
    std::string hotelName;
    BookingSystem customerBooking;
    bool isRunning = true; // Flag to control outer loop
    customerBooking.loadingCustomer();
    customerBooking.loadingHotelFile();

    while (isRunning)
    {
        std::cout << "1. Sign up" << std::endl;
        std::cout << "2. Log In" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your option here: ";
        std::cin >> loginOption;

        if (std::cin.fail() || loginOption < 1 || loginOption > 3)
        {
            std::cin.clear();                                                   // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 3." << std::endl;
            continue;
        }

        switch (loginOption)
        {
        case 1:
            // Sign up by creating a new account
            customerBooking.signUp();
            customerBooking.saveCustomerData();
            break;

        case 2:
            // Login with an existing account
            if(customerBooking.logIn())
            { // Assuming logIn returns a success flag
                std::cout << "Welcome to Hotel Booking System!" << std::endl;

                do
                {
                    std::cout << "1. View Hotels" << std::endl;
                    std::cout << "2. Search Hotels" << std::endl;
                    std::cout << "3. Book a Room" << std::endl;
                    std::cout << "4. View My Bookings" << std::endl;
                    std::cout << "5. Cancel Bookings" << std::endl;
                    std::cout << "6. Exit to Main Menu" << std::endl;
                    std::cout << "Enter your choice here: ";
                    std::cin >> choice;

                    if (std::cin.fail() || choice < 1 || choice > 6)
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid choice. Please enter a number between 1 and 6." << std::endl;
                        continue;
                    }

                    switch (choice)
                    {
                    case 1:
                        customerBooking.displayAllHotel();
                        break;
                    case 2:
                        std::cout << "==================Search Hotels==================" << std::endl;
                        std::cout << "1. Search by hotel name." << std::endl;
                        std::cout << "2. Search by Province." << std::endl;
                        std::cout << "3. Back to main menu." << std::endl;
                        std::cout << "Enter your search option here: ";
                        std::cin >> searchOption;
                        switch (searchOption)
                        {
                        case 1:
                            std::cout << "Input hotel name: ";
                            std::cin >> hotelName;
                            customerBooking.displayHotelByName(hotelName);
                            break;
                        case 2:
                            std::cout << "Input province: ";
                            std::cin >> province;
                            customerBooking.displayHotelByProvince(province);
                            break;
                        case 3:
                            std::cout << "Exit to main menu..." << std::endl;
                            break;
                        default:
                            std::cout << "Invalid option. Please enter a number between 1 and 3." << std::endl;
                            break;
                        }
                        break;

                    case 3:
                        std::cout << "==================Booking Room==================" << std::endl;
                        std::cout << "Input Hotel ID to make a room reservation: ";
                        std::cin >> hotelId;
                        customerBooking.bookRoom(hotelId);
                        break;

                    case 4:
                        std::cout << "==================View My Bookings==================" << std::endl;
                        customerBooking.viewAllBooking();
                        break;

                    case 5:
                        std::cout << "==================Cancel Bookings==================" << std::endl;
                        std::cout << "Input booking ID to cancel room reservation: ";
                        std::cin >> bookingId;
                        customerBooking.cancelRoom(bookingId);
                        break;

                    case 6:
                        std::cout << "Exiting to main menu..." << std::endl;
                        break;

                    default:
                        std::cout << "Please choose a valid option!" << std::endl;
                        break;
                    }
                } while (choice != 6);
            }
            break;

        case 3:
            isRunning = false; // Exit the outer loop
            std::cout << "Exiting the system. Goodbye!" << std::endl;
            break;

        default:
            std::cout << "Please choose a valid option!" << std::endl;
            break;
        }
    }

    customerBooking.saveCustomerData();
    customerBooking.saveHotelData();

    return 0;
}