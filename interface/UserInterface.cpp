#include <iostream>
#include <string>
#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"
#include "UserInterface.h"

#define MOTOR_FILE "data/Motorbike.txt"
#define MEMBER_FILE "data/Member.txt"

using namespace std;

UserInterface::UserInterface(){
    motorbikes = FileController::loadObjects(MOTOR_FILE, Motorbike::createObject);
    this->members = FileController::loadObjects(MEMBER_FILE, Member::createObject);
}

// safe all data (vectors of objects) back into files
void UserInterface::saveToFiles(){
    FileController::writeObjects(MOTOR_FILE, motorbikes);
}

// find and return the right member from members vector
Member* UserInterface::loginMember(int *userType, bool *isLoggedIn){
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    for (Member& mem : members){
        if (mem.username == username && mem.password == password){
            cout << "Successfully logged in!\n";
            *isLoggedIn = true;
            return &mem;
        }
    }
    cout << "Member not found. Do you want to try again? (0.No  1.Yes)\n";
    cout << "Enter your choice: ";
    cin >> *userType;
    return nullptr;
}

// Function to display member menu after successful login
int UserInterface::displayMemberMenu() {
    int choice;
    cout << "This is your menu:\n";
    cout << "0. Exit\n";
    cout << "1. View all motorbike information\n";
    cout << "2. Search for suitable motorbike rental\n";
    cout << "3. List your motorbike\n";
    cout << "4. Unlist your motorbike\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

Motorbike* UserInterface::findMyMotorbike(string ownerId){
    for (auto& mt : motorbikes){
        if (ownerId == mt.ownerId){
            return &mt;
        }
    }
    return nullptr;
}

// main function for running UserInterface
void UserInterface::runInterface(){
    int userType = 1;
    bool isLoggedIn = false;
    Member* loggedInMem = nullptr;

    // login before creating Member object
    switch (userType){
    case 0:
        cout << "Exiting Member interface...\n";
        break;
    case 1:
        do {
        loggedInMem = loginMember(&userType, &isLoggedIn);
        if (userType == 0) break;
        } while (loggedInMem == nullptr);
        break;
    default:
        cout << "Invalid choice!\n";
        break;
    }
    
    // after member logged in
    while (isLoggedIn){
        // load member's motorbike (return nullptr if not exist)
        loggedInMem->motorbike = findMyMotorbike(loggedInMem->userId);
        userType = displayMemberMenu();

        switch (userType){
        case 0:
            isLoggedIn = false;
            cout << "Logging you out...\n";
            break;
        case 1:
            break;
        default:
            cout << "Invalid choice. Please try again!\n";
            break;
        }
    }
    

    /* testing */
    // find and assign the motorbike of the member
    // members[0].motorbike = findMyMotorbike(members[0].userId);
    
    // // if the user has added their motorbike
    // if (members[0].motorbike != nullptr){
    //     members[0].motorbike->showInfo();
    // }
}