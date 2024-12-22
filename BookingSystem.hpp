#ifndef BOOKINGSYSTEM_HPP
#define BOOKINGSYSTEM_HPP

//#include "Customer.hpp"
//#include "Hotel.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;


class BookingSystem
{
private:
    //Customer *customers;
    //Hotel *hotels; 
    static int id;  
    static vector<string> name; 
    static vector<string> pswd;

public:
    //loading data from file, used when the program start
    void loadingFromFile() {
        ifstream userFile("users.txt");

        if (!userFile.is_open()) {
            cerr << "Error: Unable to open the file." << endl;
            return;
        }

        // Load users and their information from the file
        string line;
        while (getline(userFile, line)) {
            stringstream ss(line);
            int userId;
            string userName, userPswd;
            ss >> userId >> userName >> userPswd;
            name.push_back(userName);
            pswd.push_back(userPswd);
            id = max(id, userId + 1); // Update the id to the next available ID
        }

        userFile.close();
    }


    //save to file, used when finish the program
    void saveDataToFile(){
        ofstream userFile("users.txt", ios::app);  // Open the file for appending data

        if (!userFile.is_open()) {
            cerr << "Error: Unable to open the file." << endl;
            return;
        }

        // Write each user to the file
        for (int i = 0; i < name.size(); i++) {
            userFile << id << " " << name[i] << " " << pswd[i] << endl;
            id++;  // Increment the ID after saving each user
        }

        userFile.close();
    }

    //Create new account(sign up)
    void signUp(){
        ofstream userFile("users.txt", ios::app);  

        if (!userFile.is_open()) {
            cerr << "Error: Unable to open the file." << endl;
            return;
        }

        cout << "Enter your full name: "; 
        string userName;
        getline(cin, userName);  

        cout << "Enter the password: ";
        string userPswd;
        cin >> userPswd;

        // Write to file
        userFile << id << " " << userName << " " << userPswd << endl;
        name.push_back(userName);
        pswd.push_back(userPswd);

        cout << "\nNew record added!" << endl;
        cout << "Your ID is " << id << "\nPlease note down the ID as it will be required at the time of login." << endl;

        id++;  // Increment id after a new signup
        userFile.close();

    }

    //login to the system
    void logIn(){
        string loginName;
        string loginPswd;
        bool found = false;

        cout << "\nEnter your name to login: ";
        cin.ignore();  // To clear the newline character from the previous input
        getline(cin, loginName);  

        cout << "Enter your password: ";
        cin >> loginPswd;

        // Loop through the names vector to check if the name exists and the password matches
        for (int i = 0; i < name.size(); i++) {
            if (name[i] == loginName && pswd[i] == loginPswd) {
                found = true;
                cout << "Login successful! Welcome, " << name[i] << "!" << endl;
                break;
            }
        }

        if (!found) {
            cout << "Login failed. Invalid name or password. Please try again." << endl;
        }
    }


    //Add hotel
    void addHotel();

    //remove hotel from the system
    void removeHotel(int hotelId);

    //display all hotels in the system
    void displayAllHotel();

    //display hotel by province
    void displayHotelByProvince(std::string location);

    //display hotel by name 
    void displayHotelByName(std::string name);
};

// Static members initialization
int BookingSystem::id = 0;
vector<string> BookingSystem::name;
vector<string> BookingSystem::pswd;

#endif