#ifndef BOOKINGSYSTEM_HPP
#define BOOKINGSYSTEM_HPP

#include "Customer.hpp"
#include "Hotel.hpp"
#include "Booking.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <bits/stdc++.h>
#include <cctype>

class BookingSystem
{
private:
    std::vector<std::unique_ptr<Hotel>> hotels;
    std::vector<std::unique_ptr<Customer>> customers;

public:
    // Load all hotel data from file
    void loadingHotelFile()
    {
        std::string fileName = "hotelInfo.txt";
        std::ifstream file(fileName);

        if (!file.is_open())
        {
            std::cerr << "Fail to load data from " << fileName << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream linestream(line);
            std::string hotelId, hotelName, hotelLocation;
            if (std::getline(linestream, hotelId, ',') &&
                std::getline(linestream, hotelName, ',') &&
                std::getline(linestream, hotelLocation))
            {
                int id = std::stoi(hotelId);
                hotels.push_back(std::make_unique<Hotel>(id, hotelName, hotelLocation));
            }
        }
        file.close();
    }

    // Save all hotel data to file
    void saveHotelData()
    {
        std::string fileName = "hotelInfo.txt";
        std::ofstream file(fileName);

        if (!file.is_open())
        {
            std::cerr << "Fail to save data to " << fileName << std::endl;
            return;
        }

        for (const auto &hotel : hotels)
        {
            file << hotel->getHotelId() << ","
                 << hotel->getHotelName() << ","
                 << hotel->getHotelLocation() << std::endl;
        }
        file.close();
    }

    // Load all customer data from file
    void loadingCustomer()
    {
        std::string fileName = "userInfo.txt";
        std::ifstream file(fileName);

        if (!file.is_open())
        {
            std::cerr << "Fail to load data from " << fileName << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream linestream(line);
            std::string userId, userGmail, userName, gender, password;
            if (std::getline(linestream, userId, ',') &&
                std::getline(linestream, userGmail, ',') &&
                std::getline(linestream, userName, ',') &&
                std::getline(linestream, gender, ',') &&
                std::getline(linestream, password))
            {
                int id = std::stoi(userId);
                customers.push_back(std::make_unique<Customer>(id, userGmail, userName, gender, password));
            }
        }
        file.close();
    }

    // Save all customer data to file
    void saveCustomerData()
    {
        std::string fileName = "userInfo.txt";
        std::ofstream file(fileName);

        if (!file.is_open())
        {
            std::cerr << "Fail to save data to " << fileName << std::endl;
            return;
        }

        for (const auto &user : customers)
        {
            file << user->getCustomerId() << ","
                 << user->getCustomerEmail() << ","
                 << user->getCustomerName() << ","
                 << user->getCustomerGender() << ","
                 << user->getCustomerPassword() << std::endl;
        }
        file.close();
    }

    // Add a new customer
    void addCustomer(int id, const std::string &gmail, const std::string &name, const std::string &gender, const std::string &pass)
    {
        customers.push_back(std::make_unique<Customer>(id, gmail, name, gender, pass));
    }

    // Add booking
    void bookRoom(int hotelId)
    {
        for (const auto &customer : customers)
        {
            customer->loadBookingsFromFile();
            customer->addBooking(hotelId);
        }
    }

    // cancel booking
    void cancelRoom(int bookingId)
    {
        for (const auto &customer : customers)
        {
            customer->cancelBooking(bookingId);
        }
    }

    // View all booking
    void viewAllBooking()
    {
        for (const auto &customer : customers)
        {
            customer->displayCurrentBooking();
        }
    }
    // Create new account (sign up)
    void signUp()
    {
        std::string name, gmail, password, gender;
        int id;
        int trys = 0;
        std::cout << "Input your Full name: ";
        std::cin >> name;
        std::cout << "Input your gender: ";
        std::cin >> gender;

        while (trys < 3)
        {
            std::cout << "Input Gmail: ";
            std::cin >> gmail;
            if (verifyGmail(gmail))
            {
                std::cout << "Valid!" << std::endl;
                break;
            }

            std::cout << "Invalid gmail." << std::endl;
            ++trys;
        }

        trys = 0;
        while (trys < 3)
        {
            std::cout << "Input Password: ";
            std::cin >> password;
            if (verify_password(password))
            {
                std::cout << "Valid!" << std::endl;
                break;
            }

            std::cout << "Invalid password." << std::endl;
            ++trys;
        }

        // Access last customer ID and make an increment
        if (customers.empty())
        {
            id = 1; // Start with ID 1 if no customers exist
        }
        else
        {
            id = customers.back()->getCustomerId() + 1;
        }

        addCustomer(id, gmail, name, gender, password);
    }

    // login to the system
    void logIn()
    {
        std::string gmail, password;
        std::cout << "Input Gmail: ";
        std::cin >> gmail;
        std::cout << std::endl;
        std::cout << "Input password: ";
        std::cin >> password;
        for (const auto &user : customers)
        {
            if (user->getCustomerEmail() == gmail)
            {
                if (user->getCustomerPassword() == password)
                {
                    std::cout << "Login successfull..." << std::endl;
                }
            }
        }
    }

    // Add hotel
    void addHotel(int id, const std::string &name, const std::string &location)
    {
        hotels.push_back(std::make_unique<Hotel>(id, name, location));
    }

    // Display hotel room
    void displayHotelRoom(int hotelID)
    {
        for (const auto &hotel : hotels)
        {
            if (hotel->getHotelId() == hotelID)
            {
                hotel->displayAllRoom();
                return;
            }
        }
        std::cout << "Hotel not found!" << std::endl;
    }

    // display all information of the hotel
    void displayHotelInfo(int index)
    {
        if (index >= 0 && index < hotels.size())
        {
            std::cout << "Hotel name: " << hotels[index]->getHotelName() << std::endl;
            std::cout << "Hotel location: " << hotels[index]->getHotelLocation() << std::endl;
        }
    }

    // Display all hotels in the system
    void displayAllHotel()
    {
        if (hotels.empty())
        {
            std::cout << "No hotel available." << std::endl;
            return;
        }
        std::cout << "----------List of all hotels----------" << std::endl;
        for (const auto &hotel : hotels)
        {
            std::cout << "Hotel ID: " << hotel->getHotelId() << std::endl;
            std::cout << "Hotel name: " << hotel->getHotelName() << std::endl;
            std::cout << "Hotel location: " << hotel->getHotelLocation() << std::endl;
            std::cout << "-------------------------------------" << std::endl;
        }
    }

    // Display hotel by province
    void displayHotelByProvince(const std::string &location)
    {
        bool found = false;
        std::string inputLocation = toLowerCase(location);

        for (const auto &hotel : hotels)
        {
            std::string thisLocation = toLowerCase(hotel->getHotelLocation());

            if (inputLocation == thisLocation)
            {
                std::cout << "Hotel ID: " << hotel->getHotelId() << std::endl;
                std::cout << "Hotel name: " << hotel->getHotelName() << std::endl;
                std::cout << "Hotel location: " << hotel->getHotelLocation() << std::endl;
                std::cout << "-------------------------------------" << std::endl;
                found = true;
            }
        }
        if (!found)
        {
            std::cout << "Hotel with location: " << location << " not found!" << std::endl;
        }
    }
    void displayHotelByName(std::string name)
    {

        bool found = false;
        std::string inputName = toLowerCase(name);

        for (const auto &hotel : hotels)
        {
            std::string thisName = toLowerCase(hotel->getHotelName());

            if (inputName == thisName)
            {
                std::cout << "Hotel with name: " << name << std::endl;
                std::cout << "-------------------------------------" << std::endl;
                std::cout << "Hotel ID: " << hotel->getHotelId() << std::endl;
                std::cout << "Hotel name: " << hotel->getHotelName() << std::endl;
                std::cout << "Hotel location: " << hotel->getHotelLocation() << std::endl;
                std::cout << "-------------------------------------" << std::endl;

                found = true;
            }
        }
        if (!found)
        {
            std::cout << "Hotel with Name: " << name << " not found!" << std::endl;
        }
    }

    //=======create function to convert string to lowercase
    std::string toLowerCase(const std::string &str)
    {
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });
        return lowerStr;
    }
    //========verify the password
    bool verify_password(const std::string &password)
    {

        int lenght = password.length();
        if (lenght < 8 || lenght > 15)
            return false;

        bool has_upper = false;
        bool has_lower = false;
        bool has_symbol = false;
        bool has_digit = false;

        for (int i = 0; i < lenght; i++)
        {

            if (isupper(password[i]))
                has_upper = true;
            if (islower(password[i]))
                has_lower = true;
            if (isdigit(password[i]))
                has_digit = true;
            if (ispunct(password[i]))
                has_symbol = true;
        }

        if ((has_upper && has_lower && has_digit && has_symbol))
            return true;
    }
    //========verify gmail
    bool verifyGmail(const std::string &gmail)
    {
        if (!isalpha(gmail[0]))
            return false; // false if first letter is not an alpha
        int At = -1, Dot = -1;
        for (int i = 0; i < gmail.length(); i++)
        {
            // If the character is '@'
            if (gmail[i] == '@')
            {
                At = i;
            }
            // If character is '.'
            else if (gmail[i] == '.')
            {
                Dot = i;
            }
        }
        if (At == -1 || Dot == -1)
            return false;
        if (At > Dot)
            return false;
        return !(Dot >= (gmail.length() - 1));
    }
};

#endif