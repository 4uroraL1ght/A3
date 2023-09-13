#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Motorbike.h"

using namespace std;

Motorbike::Motorbike(string motorId, string ownerId, string model, string color, string engineSize, string transmissionMode, string description,
unsigned int yearMade, double consumingPoints, string city, bool isAvailable, double minRenterRating, double ratingScore)
: motorId(motorId), ownerId(ownerId), model(model), color(color), engineSize(engineSize), transmissionMode(transmissionMode), 
description(description), yearMade(yearMade), consumingPoints(consumingPoints), city(city), isAvailable(isAvailable), 
minRenterRating(minRenterRating), ratingScore(ratingScore){}

Motorbike::~Motorbike(){}

// format for saving into txt file
string Motorbike::toString(){
    return (motorId + ',' + ownerId + ',' + model + ',' + color + ',' + engineSize + ',' + transmissionMode + ',' + description +
    ',' + to_string(yearMade) + ',' + to_string(consumingPoints) + ',' + city + ',' + to_string(isAvailable) + ','   // 1 is true, 0 false
    + to_string(minRenterRating) + ',' + to_string(ratingScore) + "\n");
}

// show info in short - used for listing many motorbikes
void Motorbike::showInfo(){
    cout << motorId << ";\tOwner ID: " << ownerId << ";\tModel: " << model << ";\tColor: " << color << ";\tEngine Size: " << 
    engineSize << ";\tYear Made: " << yearMade << ";\tAvailable: " << (isAvailable ? "Yes":"No") << endl; 
}

// show detail info
void Motorbike::showInfoDetail(){
    cout << "------ Motorbike information ------" << endl;
    cout << "Motorbike ID: " << motorId << "\tOwner ID: " << ownerId << "\tCity: " << city << endl;
    cout << "Model: " << model << "\tColor: " << color << "\nEngine Size: " << engineSize << endl;
    cout << "Transmission Mode: " << transmissionMode << "\tYear Made: " << yearMade << endl;
    cout << "Description: " << description << endl;
    cout << "Consuming Point: " << consumingPoints << endl;
    cout << "Rating Score: " << ratingScore << "\tAvailabe: " << (isAvailable ? "Yes":"No");
    cout << "\n-----------------------------------\n";
    cout << endl;
}

Motorbike Motorbike::createObject(string line){
    stringstream ss(line);
    string temp, motorId, ownerId, model, color, engineSize, transmissionMode, description, available, city;
    double consumingPoints=0, minRenterRating=0, ratingScore=0;
    unsigned int year;
    getline(ss, motorId, ',');
    getline(ss, ownerId, ',');
    getline(ss, model, ',');
    getline(ss, color, ',');
    getline(ss, engineSize, ',');
    getline(ss, transmissionMode, ',');
    getline(ss, description, ',');
    getline(ss, temp, ',');
    year = stoi(temp);
    getline(ss, temp, ',');
    consumingPoints = stod(temp);
    getline(ss, city, ',');
    getline(ss, temp, ',');
    bool isAvailable = stoi(temp);
    getline(ss, temp, ',');
    minRenterRating = stod(temp);
    getline(ss, temp, ',');
    ratingScore = stod(temp);
    return Motorbike(motorId, ownerId, model, color, engineSize, transmissionMode, description,
    year, consumingPoints, city, isAvailable, minRenterRating, ratingScore);
}

// make a request for renting the motorbike
// void Motorbike::requestToRent(Member renter, int bday, int bmonth, int eday, int emonth){
// }

// show information of all requests
// void Motorbike::viewRequests(){
//     if (rentals.size() != 0){
//         for (Rental rt : rentals){
//         rt.showInfo();
//         }
//     } else cout << "This motorbike has no requests.\n";
// }

// display the current settings of listed values
bool Motorbike::changeCurrentSettings(){
    unsigned int choice;
    cout << "----- Your current setting for the motorbike -----\n";
    cout << "Available time: From " << "to " << endl;
    cout << "Consuming points (per day): " << consumingPoints << endl;
    cout << "Minimum required renter-rating: " << minRenterRating << endl;
    cout << "Do you want to modify the settings? ( 0.No  1.Yes )\n";
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice > 1){
        cout << "Invalid choice. No changes are made.\n";
        return 0;
    } else return choice;
}

// list the motorbike and set constraints
void Motorbike::listMotorbike(){
    if (changeCurrentSettings()){
        // Available time settings

        cout << "Enter consuming points (per day): ";
        cin >> consumingPoints;
        cout << "Enter minimum required renter-rating: ";
        cin >> minRenterRating;
    }
    // make the motorbike available
    this->isAvailable = true;
}

// unlist the motorbike: make it unavailable
void Motorbike::unlistMotorbike(){
    this->isAvailable = false;
    cout << "Unlisted your motorbike.\n";
}

void Motorbike::viewReviews(){
    // view data from MotorbikeReview.txt
}
