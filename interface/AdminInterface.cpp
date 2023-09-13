#include <iostream>
#include <string>
#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"
#include "AdminInterface.h"

#define MOTOR_FILE "data/Motorbike.txt"
#define MEMBER_FILE "data/Member.txt"

using namespace std;

AdminInterface::AdminInterface(){
    this->motorbikes = FileController::loadObjects(MOTOR_FILE, Motorbike::createObject);
    this->members = FileController::loadObjects(MEMBER_FILE, Member::createObject);
}

// safe all data (vectors of objects) back into files
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
    cout << "3. View request information\n";
    cout << "4. View rental information\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}
