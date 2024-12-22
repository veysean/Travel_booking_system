#include "BookingSystem.hpp"

int main() {
    // Create an instance of BookingSystem
    BookingSystem system;

    system.loadingFromFile();

    // Simulate user sign up
    system.signUp();

    // Simulate user login
    system.logIn();

    // Save all data to file
    system.saveDataToFile();

    return 0;
}