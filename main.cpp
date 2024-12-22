#include <iostream>

#include "BookingSystem.hpp"

using namespace std;
int main()
{

    int chioce;
    int loginOption;
    BookingSystem customerBooking;
    do
    {
        cout << "1. Sign up" << endl;
        cout << "2. Log In" << endl;
        switch (loginOption)
        {
        case 1:
            // sign up by create new account
            customerBooking.signUp();
            break;
        case 2:
            // Login with exist account
            customerBooking.logIn();
            cout << "Welcome to Hotel Booiking System!" << endl;
            do
            {
                cout << "1. View Hotels" << endl;
                cout << "2. Search Hotels" << endl;
                cout << "3. Book a Room" << endl;
                cout << "4. View My Bookings" << endl;
                cout << "5. Cancel Bookings" << endl;
                cout << "6. Exit" << endl;
                cout << "Enter your choice here : ";
                cin >> chioce;
                switch (chioce)
                {
                case 1:

                    break;
                case 2:

                    break;
                case 3:

                    break;
                case 4:

                    break;
                case 5:
                    break;
                case 6:

                    break;
                default:
                    cout << "Please, choose the the correct options!" << endl;
                    break;
                }

            } while (chioce <= 6);
        default:
            cout << "Please, choose the the correct options!" << endl;
            break;
        }

    } while (loginOption <= 2);

    return 0;
}