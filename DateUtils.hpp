#ifndef DATEUTILS_HPP
#define DATEUTILS_HPP

#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <stdexcept>

class DateUtils
{
public:
    static bool isLeapYear(int year)
    {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    static int daysInMonth(int month, int year)
    {
        switch (month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
        }
    }

    static void splitDate(const std::string &date, int &day, int &month, int &year)
    {
        std::stringstream ss(date);
        std::string dayStr, monthStr, yearStr;
        std::getline(ss, dayStr, '-');
        std::getline(ss, monthStr, '-');
        std::getline(ss, yearStr);
        day = std::stoi(dayStr);
        month = std::stoi(monthStr);
        year = std::stoi(yearStr);
    }

    static std::string calculateCheckOutDate(const std::string &checkIn, int duration)
    {
        int day, month, year;
        splitDate(checkIn, day, month, year);
        day += duration - 1;
        while (day > daysInMonth(month, year))
        {
            day -= daysInMonth(month, year);
            month++;
            if (month > 12)
            {
                month = 1;
                year++;
            }
        }
        return (day < 10 ? "0" : "") + std::to_string(day) + "-" +
               (month < 10 ? "0" : "") + std::to_string(month) + "-" +
               std::to_string(year);
    }

    static std::string isValidDateAndIncrement(const std::string &date, int days)
    {
        std::regex datePattern(R"(\b(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-\d{4}\b)");
        if (!std::regex_match(date, datePattern))
        {
            throw std::invalid_argument("Invalid date format");
        }

        int day, month, year;
        splitDate(date, day, month, year);
        day += days;
        while (day > daysInMonth(month, year))
        {
            day -= daysInMonth(month, year);
            month++;
            if (month > 12)
            {
                month = 1;
                year++;
            }
        }
        return (day < 10 ? "0" : "") + std::to_string(day) + "-" +
               (month < 10 ? "0" : "") + std::to_string(month) + "-" +
               std::to_string(year);
    }
};

#endif