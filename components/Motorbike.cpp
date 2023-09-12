#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../components/Motorbike.h"

using namespace std;

Motorbike::Motorbike(string motorId, string model, string color, string engineSize, string transmissionMode, string description,
unsigned int yearMade, double consumptionPoint, bool isAvailable, double minRenterRating, double ratingScore)
: motorId(motorId), model(model), color(color), engineSize(engineSize), transmissionMode(transmissionMode), 
description(description), yearMade(yearMade), consumptionPoint(consumptionPoint), isAvailable(isAvailable), minRenterRating(minRenterRating), 
ratingScore(ratingScore){
}

Motorbike::~Motorbike(){}

// format for saving into txt file
string Motorbike::toString(){
    return (motorId + ',' + model + ',' + color + ',' + engineSize + ',' + transmissionMode + ',' + description +
    ',' + to_string(yearMade) + ',' + to_string(consumptionPoint) + ',' + to_string(isAvailable) + ','   // 1 is true, 0 false
    + to_string(minRenterRating) + ',' + to_string(ratingScore) + "\n");
}

void Motorbike::showInfo(){
    cout << "--- Motorbike information ---" << endl;
    cout << "Motorbike ID: " << motorId << "\tOwner's Name: " << "\tOwner ID: " << endl;
    cout << "Model: " << model << "\tColor: " << color << "\nEngine Size: " << engineSize << endl;
    cout << "Transmission Mode: " << transmissionMode << "\tYear Made: " << yearMade << endl;
    cout << "Description: " << description << endl;
    cout << "Consumption Point: " << consumptionPoint << endl;
    cout << "Rating Score: " << ratingScore << "\tAvailability: " << boolalpha << isAvailable << endl;
    cout << endl;
}

Motorbike Motorbike::createObject(string line){
    stringstream ss(line);
    string temp, motorId, model, color, engineSize, transmissionMode, description, available;
    double consumptionPoint=0, minRenterRating=0, ratingScore=0;
    unsigned int year;
    getline(ss, motorId, ',');
    getline(ss, model, ',');
    getline(ss, color, ',');
    getline(ss, engineSize, ',');
    getline(ss, transmissionMode, ',');
    getline(ss, description, ',');
    getline(ss, temp, ',');
    year = stoi(temp);
    getline(ss, temp, ',');
    consumptionPoint = stod(temp);
    getline(ss, temp, ',');
    bool isAvailable = stoi(temp);
    getline(ss, temp, ',');
    minRenterRating = stod(temp);
    getline(ss, temp, ',');
    ratingScore = stod(temp);
    return Motorbike(motorId, model, color, engineSize, transmissionMode, description,
    year, consumptionPoint, isAvailable, minRenterRating, ratingScore);
}

// make a request for renting the motorbike
void Motorbike::requestToRent(Member renter, int bday, int bmonth, int eday, int emonth){
    // Rental newRental(renter, )
}

// show information of all requests
void Motorbike::viewRequests(){
    if (rentals.size() != 0){
        for (Rental rt : rentals){
        rt.showInfo();
        }
    } else cout << "This motorbike has no requests.\n";
}

void Motorbike::viewReviews(){
    // view data from MotorbikeReview.txt
}

void Motorbike::listRenterFilter(){
    // take the min required renter rating from data & set to minRenterRating
}

void Motorbike::unlistRenterFilter(){
    // remove rating filter for renters
    this->minRenterRating = 0;
}