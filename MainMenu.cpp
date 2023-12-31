#include <iostream>
#include <string>
#include <vector>
#include "components/Motorbike.h"
#include "action/FileController.h"
#include "interface/AdminInterface.h"
#include "interface/UserInterface.h"
#include "interface/GuestInterface.h"
using namespace std;

// Function to display the welcome screen
void displayWelcomeScreen() {
    cout << "EEET2482/COSC2082 ASSIGNMENT\n";
    cout << "MOTORBIKE RENTAL APPLICATION\n";
    cout << "Instructor: Dr. Ling Huo Chong\n";
    cout << "Group: Group 20\n";
    cout << "s3938231, Ong Gia Man\n";
    cout << "s3932151, Nguyen Le Thu Nhan\n";
    cout << "s3926829, Ngo Minh Hoang\n";
    cout << "s3916570, Vo Minh Thien An\n";
}

// Function to display the main menu for different user types
int displayMainMenu(int userType) {
    int choice;

    switch (userType) {
        case 1: // Guest
            return 1;
            break;
        case 2: // Member
            cout << "This is your menu:\n";
            cout << "0. Exit\n";
            cout << "1. Login\n";
            break;
        case 3: // Admin
            cout << "This is your menu:\n";
            cout << "0. Exit\n";
            cout << "1. Login\n";
            break;
        default:
            cout << "Invalid user type.\n";
            return -1;
    }

    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int main(int argc, char const *argv[])
{
    int userType;
    string username, password;
    bool stopRun = true;

    displayWelcomeScreen();
    do{
        stopRun = true;
        cout << "\nUse the app as 1. Guest 2. Member 3. Admin\n";
        cout << "Enter your choice: ";
        cin >> userType;

        // different menu options based on user type
        int mainMenuChoice = displayMainMenu(userType);

        switch (mainMenuChoice) {
            case 0:
                cout << "Exiting the application...\n";
                break;
            case 1:
                if (userType == 1) {
                    // call register function (not implemented)
                        GuestInterface guestInterface;
                        stopRun = guestInterface.runInterface();
                }
                else if (userType == 2) {
                    // if user chooses Member type
                    // create UserInterface and run interface (perform login inside)
                        UserInterface userInterface;
                        userInterface.runInterface();
                    }
                    
                else if (userType == 3) {
                    // create AdminInterface and run
                        AdminInterface adminInterface;
                        adminInterface.runInterface();
                    }
                else {
                    cout << "Invalid user type.\n";
                }
                break;
            default:
                break;
            }
    } while (!stopRun);
    
    
    cout << "Good bye and see you again!\n";
    return 0;
}