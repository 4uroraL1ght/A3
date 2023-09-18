#include <iostream>
#include <string>
#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"
#include "AdminInterface.h"

#define MOTOR_FILE "data/Motorbike.txt"
#define MEMBER_FILE "data/Member.txt"
#define RENTAL_FILE "data/Rental.txt"

using namespace std;

AdminInterface::AdminInterface(){
    this->motorbikes = FileController::loadObjects(MOTOR_FILE, Motorbike::createObject);
    this->members = FileController::loadObjects(MEMBER_FILE, Member::createObject);
    this->rentals = FileController::loadObjects(RENTAL_FILE, Rental::createObject);
    loadRentalComponents();
}

void AdminInterface::loadRentalComponents(){
    for (Rental& r : rentals){
        r.loadComponents(motorbikes, members);
    }
}

// save all data (vectors of objects) back into files
void AdminInterface::saveToFiles(){
    FileController::writeObjects(MOTOR_FILE, motorbikes);
}

// Function to display admin menu after successful login
int AdminInterface::displayAdminMenu() {
    int choice;
    cout << "This is your menu:\n";
    cout << "0. Exit\n";
    cout << "1. View member information\n";
    cout << "2. View motorbike information\n";
    cout << "3. View rental information\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void AdminInterface::displayMembers(){
    for (int i = 0; i < members.size() ; i++){
        cout << i+1 << ". ";
        members[i].showInfo();
    }
}

void AdminInterface::displayMotorbikes(){
    for (int i = 0; i < motorbikes.size() ; i++){
        cout << i+1 << ". ";
        motorbikes[i].showInfo();
    }
}

void AdminInterface::displayRentals(){
    for (int i = 0; i < rentals.size() ; i++){
        cout << i+1 << ". ";
        rentals[i].showInfo();
    }
}

void AdminInterface::runInterface(){
    Admin admin;
    bool isLoggedIn = admin.logging();
    int userType;
    while (isLoggedIn){    // if log in successfully
        userType = displayAdminMenu();
        switch (userType){
        case 0:     // log out
            isLoggedIn = false;
            cout << "Logging you out...\n";
            break;
        case 1:     // view all members
            displayMembers();
            break;
        case 2:     // view all motorbikes
            displayMotorbikes();
            break;
        case 3:     // view all rentals
            displayRentals();
            break;
        default:
            cout << "Invalid choice!\n";
            break;
        }
    }
}