#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <fstream>
#include <sstream>

class Room
{
private:
    // 1 mean room is available and 0 room unavailable
    bool available;
    // price of the room
    double price;
    // typs of room like 1bed or 2beds
    std::string roomType;
    
    //Helper function to check if a year is a leap year
    bool isLeapYear(int year){
        return (year % 4 == 0 && year %100 != 0) || (year % 400 == 0);
    }

    //Helper function to get the number of days in a month
    int daysInMonth(int month, int year){
        switch (month)
        {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                return 31;
            case 4: case 6: case 9: case 11:
                return 30;
            case 2:
                return isLeapYear(year) ? 29 : 28;
            default:
                return 0;
        }

    }
//Helper function to check if the room exists in the hotel's room list
bool isRoomInHotelList(std::string &roomNum, std::string &hotel)
{
    std::ifstream hotelFile(hotel + "_room_list.txt");
    if(!hotelFile.is_open()){
        std::cout<< "Unable to open the file." << std::endl;
        return false;
    }

    std::string line;
    while(std::getline(hotelFile,line)){
        std::istringstream iss(line);
        std::string roomNumber;
        if(iss>>roomNumber){
            if(roomNumber == roomNum){
                hotelFile.close();
                return true;
            }
        }
    }
    hotelFile.close();
    return false;
}

public:
    // Constructor
    Room(double price, std::string &type)
    {
        this->price = price;
        this->roomType = type;
        this->available = 1;
    }

    // check if room is available
    void isRoomAvailable(std::string &hotel,std::string &roomNum, int checkInDay, int checkInMonth, int checkInYear, int numberOfDays)
    {
        //Check if the room exists in the hotel's room list
        if (!isRoomInHotelList(roomNum, hotel))
        {
            std::cout << "Room " << roomNum << " does not exist in " << hotel << "." << std::endl;
            available = false;
            return;
        }
        if(checkInYear < 2025){
            std::cout << "Booking year must be greater than 2025" << std::endl;
            available = false;
            return;
        }

        //Check availability based on booking info
        std::ifstream File(hotel + "_booking_info.txt");
        if (!File.is_open())
        {
            std::cout << "Unable to open booking info file for " << hotel << "." << std::endl;
            return;
        }
        std::string line;
        available = true;

        while(std::getline(File, line)){
            std::istringstream iss(line);
            std::string userName, bookedRoom;
            int day,month,year,stayDuration;

            if(iss>>userName>>bookedRoom>>day>>month>>year>>stayDuration){
                if(bookedRoom == roomNum){
                        
                    int checkOutDay = day + stayDuration -1;
                    int checkOutMonth = month;
                    int checkOutYear = year;

                    if(checkOutDay > daysInMonth(checkOutMonth, checkOutYear))
                    {
                        checkOutDay -= daysInMonth(checkOutMonth, checkOutYear);
                        checkOutMonth++;

                        if(checkOutMonth > 12)
                        {
                            checkOutMonth = 1;
                            checkOutYear++;
                        }
                    }

                    if(checkOutDay > 30){
                        checkOutDay -= 30;
                        checkOutMonth++;

                        if(checkOutMonth > 12){
                            checkOutMonth = 1;
                            checkOutYear++;
                        }
                    }

                    //check the check in date
                    for(int i=0; i<numberOfDays; i++){
                        int currentDay = checkInDay;
                        int currentMonth = checkInMonth;
                        int currentYear = checkInYear;

                        if(currentDay > daysInMonth(currentMonth, currentYear)){
                            currentDay -= daysInMonth(currentMonth, currentYear);
                            currentMonth++;

                            if(currentMonth>12){
                                currentMonth = 1;
                                currentYear++;
                            }
                        }
                        //check if the booking period available
                        if((currentYear == year && currentMonth == month && currentDay >= day && currentDay <= checkOutDay)){
                            available = false;
                            break;
                        }
                        checkInDay++;
                    }
                }
            }
        }
        File.close();
    
    }

    // display room info( price & type)
    void roomDetail(std::string &hotel, std::string &roomNum)
    {  
        std::ifstream roomFile(hotel + "_room_list.txt");
        if(roomFile.is_open()){
            std::string line;

            while(std::getline(roomFile,line)){
                std::istringstream iss(line);
                std::string room;
                float roomPrice;
                std::string type;

                if(iss>>room>>roomPrice>>type){
                    if(room==roomNum){
                        this->price = roomPrice;
                        this->roomType = type;
                        break;
                    }
                }

            }
            roomFile.close();
        }
        else{
            std::cout<<"Unable to open the file." << std::endl;
        }
        std::cout<< "Room Number: " << roomNum << std::endl;
        std::cout << "Room Type: " << roomType << std::endl;
        std::cout << "Price: " << price << std::endl;
        std::cout << "Available: "<< (available ? "Yes" : "No") << std::endl;
    }
};

#endif