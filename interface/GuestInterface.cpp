#include <iostream>
#include <string>
#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"
#include "GuestInterface.h"

#define MOTOR_FILE "data/Motorbike.txt"

using namespace std;

GuestInterface::GuestInterface(){
    this->motorbikes = FileController::loadObjects(MOTOR_FILE, Motorbike::createObject);
}

void GuestInterface::saveToFiles(){
    FileController::writeObjects(MOTOR_FILE, motorbikes);
}

// Function to display guest menu
int GuestInterface::displayGuestMenu() {
    int choice;
    cout << "This is your menu:\n";
    cout << "0. Exit\n";
    cout << "1. Register\n";
    cout << "2. View motorbike information\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void GuestInterface::displayMotorbikes(){
    for (int i = 0; i < motorbikes.size() ; i++){
        cout << i+1 << ". ";
        motorbikes[i].showInfo();
    }
}

void GuestInterface::registerMember(){
        cout << "=== Member Registration ===" << endl;

        // Set default values
        double creditPoints = 20.0;
        double renterRating = 0.0;
        bool isRenting = false;

        // Prompt the user to input registration details
        string userId = generateUniqueUserId();
        string username, password, fullName, phoneNumber, idType, passportNum, driverLicenseNum, expiryDate, city;
        
        cout << "Enter username: "; cin >> username;
        cout << "Enter password: "; cin >> password;
        cout << "Enter your full name: "; getline(cin, fullName); cin.ignore();
        cout << "Enter your phone number: "; cin >> phoneNumber;
        cout << "Enter your ID type (Citizen ID/Passport): "; getline(cin, idType); cin.ignore();
        cout << "Enter your ID/passport number: "; cin >> passportNum;
        cout << "Enter your driver's license number: "; cin >> driverLicenseNum;
        cout << "Enter your license expiry date (dd-mm-yyyy format): "; cin >> expiryDate;
        cout << "Enter your city: "; cin.ignore(); getline(cin, city);

        // Appending new member details
        ofstream memberFile("data/Member.txt", ios::app);
        if (!memberFile.is_open()) {
            cout << "Unable to open Member.txt for writing." << endl;
            return;
        }

        // Write new member's details to the file
        memberFile << userId << "," << username << "," << password << "," << fullName << "," << phoneNumber << ",";
        memberFile << idType << "," << passportNum << "," << driverLicenseNum << "," << expiryDate << ",";
        memberFile << city << "," << creditPoints << "," << renterRating << "," << isRenting << endl;

        // Close the file
        memberFile.close();

        cout << "Do you want to register a motorbike? (1 for yes, 2 for no): ";
        string hasMotorbike;
        cin >> hasMotorbike;

        // Initialize motorbike attributes
        string motorId = generateUniqueMotorId();
        string model = "None";
        string color = "None";
        string engineSize = "None";
        string transmissionMode = "None";
        string description = "None";
        unsigned int yearMade = 2023;
        double consumingPoints = 0.0;
        bool isAvailable = false;
        double minRenterRating = 0.0;
        double ratingScore = 0.0;

        if (hasMotorbike == "1") {
            cout << "Enter motorbike model: "; getline(cin, model); cin.ignore();
            cout << "Enter motorbike color: "; getline(cin, color); cin.ignore();
            cout << "Enter motorbike engine size: "; getline(cin, engineSize); cin.ignore();
            cout << "Enter motorbike transmission mode: "; getline(cin, transmissionMode); cin.ignore();
            cout << "Enter motorbike description: "; getline(cin, description); cin.ignore();
            cout << "Enter motorbike year made: "; cin >> yearMade;
            cout << "Enter motorbike consuming points: "; cin >> consumingPoints;
            cout << "Enter motorbike city: "; getline(cin, city); cin.ignore(); 
            cout << "Is the motorbike available? (1 for yes, 0 for no): "; cin >> isAvailable;
            cout << "Enter the minimum renter rating for the motorbike: "; cin >> minRenterRating;

        ofstream motorbikeFile("data/Motorbike.txt", ios::app);
        if (!motorbikeFile.is_open()) {
            cout << "Error: Unable to open Motorbike.txt for writing." << endl;
            return;
        }

        // Append motorbike information to Motorbike.txt
        motorbikeFile << motorId << "," << userId << "," << model << "," << color << "," << engineSize << ",";
        motorbikeFile << transmissionMode << "," << description << "," << yearMade << ",";
        motorbikeFile << consumingPoints << "," << city << "," << isAvailable << ",";
        motorbikeFile << minRenterRating << endl;
        motorbikeFile.close();
    }


        cout << "Registration successful!" << endl;
    }

string GuestInterface::generateUniqueUserId() {
        string uniqueId;
        string lastID;
        ifstream file("data/Member.txt");

        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
            // Split the line into parts using ',' as delimiter
                size_t pos = line.find(',');
                if (pos != string::npos) {
                    string id = line.substr(0, pos);
                    lastID = id; // Update lastID with the latest ID found
                }   
            }
            file.close();
        } else {
            cout << "Unable to open file" << endl;
        }
        // Extract the numeric part of the last user ID (e.g., "MB1" => "1")
        string numericPart = lastID.substr(2);

        // Convert the numeric part to an integer, increment it, and format it back to a string
        int nextNumericValue = stoi(numericPart);
        nextNumericValue++;
        uniqueId = "MB" + to_string(nextNumericValue);

        return uniqueId;
    }

string GuestInterface::generateUniqueMotorId() {
    string uniqueId;
        string lastID;
        ifstream file("data/Motorbike.txt");

        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
            // Split the line into parts using ',' as delimiter
                size_t pos = line.find(',');
                if (pos != string::npos) {
                    string id = line.substr(0, pos);
                    lastID = id; // Update lastID with the latest ID found
                }   
            }
            file.close();
        } else {
            cout << "Unable to open file" << endl;
        }
        // Extract the numeric part of the last user ID (e.g., "M1" => "1")
        string numericPart = lastID.substr(1);

        // Convert the numeric part to an integer, increment it, and format it back to a string
        int nextNumericValue = stoi(numericPart);
        nextNumericValue++;
        uniqueId = "M" + to_string(nextNumericValue);

        return uniqueId;
    }

void GuestInterface::runInterface(){
        while (true){   
        int userType = displayGuestMenu();
        switch (userType){
        case 0:     // log out
            cout << "Logging you out...\n";
            break;
        case 1:     // register to be new member
            registerMember();
            break;
        case 2:     // view all motorbikes
            displayMotorbikes();
            break;
        default:
            cout << "Invalid choice!\n";
            break;
        }
    }
        
}
