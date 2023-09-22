/* Acknowledgment:
[1] cplusplus.com. "<ctime> (time.h)." cplusplus.com. [Online]. Available: https://cplusplus.com/reference/ctime/ (accessed Sep. 21, 2023).
[2] cppreference.com. "std::ctime." cppreference.com. [Online]. Available: https://cplusplus.com/reference/ (accessed Sep. 21, 2023). */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Motorbike.h"

using namespace std;

Motorbike::Motorbike(string motorId, string ownerId, string model, string color, string engineSize, string transmissionMode, 
string description, unsigned int yearMade, double consumingPoints, string city, bool isAvailable, double minRenterRating, 
double ratingScore, int beginDay, int beginMonth, int duration)
: motorId(motorId), ownerId(ownerId), model(model), color(color), engineSize(engineSize), transmissionMode(transmissionMode), 
description(description), yearMade(yearMade), consumingPoints(consumingPoints), city(city), isAvailable(isAvailable), 
minRenterRating(minRenterRating), ratingScore(ratingScore), beginDay(beginDay), beginMonth(beginMonth), duration(duration) {
    beginDate.tm_mday = beginDay;
    beginDate.tm_mon = beginMonth;
    beginDate.tm_year = 2023 - 1900;
    calculateEndDate();    // call function to calculate end date
}

Motorbike::~Motorbike(){}

// format for saving into txt file
string Motorbike::formatForSaving(){
    return (motorId + ',' + ownerId + ',' + model + ',' + color + ',' + engineSize + ',' + transmissionMode + ',' + description +
    ',' + to_string(yearMade) + ',' + to_string(consumingPoints) + ',' + city + ',' + to_string(isAvailable) + ','   // 1 is true, 0 false
    + to_string(minRenterRating) + ',' + to_string(ratingScore) + ',' + to_string(beginDay) + ',' + to_string(beginMonth) + ',' + to_string(duration) + "\n");
}

// show info in short - used for listing many motorbikes
void Motorbike::showInfo(){
    cout << "Motor ID: " << motorId << ";\tOwner ID: " << ownerId << ";\tModel: " << model << ";\tColor: " << color << ";\tEngine Size: " << 
    engineSize << ";\tYear Made: " << yearMade << ";\tAvailable: " << (isAvailable ? "Yes":"No") << endl; 
}

// show detail info
void Motorbike::showInfoDetail(){
    cout << "\n\t------ Motorbike information ------" << endl;
    cout << "Motorbike ID: " << motorId << "\tOwner ID: " << ownerId << "\tCity: " << city << endl;
    cout << "Model: " << model << "\tColor: " << color << "\nEngine Size: " << engineSize << endl;
    cout << "Transmission Mode: " << transmissionMode << "\tYear Made: " << yearMade << endl;
    cout << "Description: " << description << endl;
    cout << "Consuming Point: " << consumingPoints << "\nMinimun rating required for renters: " << minRenterRating << endl; 
    cout << "Rating Score: " << ratingScore << "\t\tAvailable: " << (isAvailable ? "Yes":"No");
    cout << "\nAvailable within " << duration << " days: From: " << beginDate.tm_mday << '/' <<
    beginDate.tm_mon << "/2023 to " << endDate.tm_mday << "/" << endDate.tm_mon << "/2023\n";
    cout << "--------------------------------------------------------\n";
    cout << endl;
}

Motorbike Motorbike::createObject(string line){
    stringstream ss(line);
    string temp, motorId, ownerId, model, color, engineSize, transmissionMode, description, available, city;
    double consumingPoints=0, minRenterRating=0, ratingScore=0;
    unsigned int year, beginDay, beginMonth, duration;
    getline(ss, motorId, ',');
    getline(ss, ownerId, ',');
    getline(ss, model, ',');
    getline(ss, color, ',');
    getline(ss, engineSize, ',');
    getline(ss, transmissionMode, ',');
    getline(ss, description, ',');
    getline(ss, temp, ','); year = stoi(temp);
    getline(ss, temp, ','); consumingPoints = stod(temp);
    getline(ss, city, ',');
    getline(ss, temp, ','); bool isAvailable = stoi(temp);
    getline(ss, temp, ','); minRenterRating = stod(temp);
    getline(ss, temp, ','); ratingScore = stod(temp);
    getline(ss, temp, ','); beginDay = stoi(temp);
    getline(ss, temp, ','); beginMonth = stoi(temp);
    getline(ss, temp, ','); duration = stoi(temp);
    return Motorbike(motorId, ownerId, model, color, engineSize, transmissionMode, description,
    year, consumingPoints, city, isAvailable, minRenterRating, ratingScore, beginDay, beginMonth, duration);
}

// make a request for renting the motorbike
Rental* Motorbike::requestToRent(Member* renter, string lastRentalId){
    cout << "----- Create renting request (Year 2023) -----\n";
    cout << "(Please enter the following rental information)\n";
    int bday, bmonth, duration;
    cout << "Beginning day: "; cin >> bday;
    cout << "Beginning month: "; cin >> bmonth;
    if (!isValidDate(bday, bmonth)) {
        cout << "Invalid date! Failed to request.\n";
        return nullptr;
    }
    cout << "Duration (How many days do you want to rent?): "; cin >> duration;
    string rentalId = FileController::generateUniqueId(lastRentalId, "RE", 2);
    Rental *rental = new Rental(rentalId, motorId, ownerId, bday, bmonth, duration, "requested", false, false);
    rental->motorbike = this;
    rental->renter = renter;

    // if (!rental->isValidRentalDate()){  // if the requested date is invalid
    //     cout << "Your requested date is invalid with the motorbike!\n";
    //     return nullptr;
    // }
    if (rental->hasEnoughCredit()){
        cout << "Your request has been created!\n";
        return rental;
    } else {    // if the renter doesn't have enough credit points
        cout << "You don't have enough credit points to pay for this rental!\n";
        cout << "Do you want to perform a top up? (0.No 1.Yes)\n";
        int choice; cin >> choice;
        if (choice == 1) renter->performATopUp();
    }
    return nullptr;
}

// display the current settings of listed values
bool Motorbike::changeCurrentSettings(){
    unsigned int choice;
    cout << "\n----- Your current setting for the motorbike -----\n";
    cout << "Available time: From " << beginDay << '/' << beginMonth << "/2023 to " 
    << endDate.tm_mday << '/' << endDate.tm_mon << '/' << endDate.tm_year << endl;
    cout << "Duration: " << duration << " days.\n";
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
    int bday, bmonth;
    if (changeCurrentSettings()){
        // Available time settings
        cout << "Set available date\n";
        cout << "Enter begin date: ";
        cin >> bday;
        cout << "Enter begin month: ";
        cin >> bmonth;
        if (isValidDate(bday, bmonth)){
            cout << "Enter available time (days): ";
            cin >> duration;
            cout << "Enter consuming points (per day): ";
            cin >> consumingPoints;
            cout << "Enter minimum required renter-rating: ";
            cin >> minRenterRating;
            beginDate.tm_mday = bday;
            beginDate.tm_mon = bmonth;
            calculateEndDate();     // update the endDate
        } else {
            cout << "Invalid date! Failed to list the motorbike.\n";
            return;
        }
    }
    // make the motorbike available
    this->isAvailable = true;
    cout << "You have listed your motorbike!\n";
    showInfoDetail();
}

// unlist the motorbike: make it unavailable
void Motorbike::unlistMotorbike(){
    this->isAvailable = false;
    cout << "Unlisted your motorbike.\n";
}

void Motorbike::calculateEndDate(){
    // create int array to store days in each month (not include leap years)
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // store begin date in temp variable to calculate the end date
    tm endDateTemp = beginDate;
    endDateTemp.tm_mday += duration; // add the duration to begin day

    // handle rollover of days
    while (endDateTemp.tm_mday > daysInMonth[endDateTemp.tm_mon - 1]) {
        endDateTemp.tm_mday -= daysInMonth[endDateTemp.tm_mon - 1];
        endDateTemp.tm_mon++;
        if (endDateTemp.tm_mon == 12) { // switch to the next year
            endDateTemp.tm_mon = 0;
            endDateTemp.tm_year++;
        }
    }
    endDate = endDateTemp;
}

bool Motorbike::isValidDate(int day, int month){
    // check if the month is valid
    if (month < 1 || month > 12) {
        return false;
    }
    // check if the day is valid
    if (day < 1 || day > 31) {
        return false;
    }
    // check for months with less than 31 days
    if (day == 31 && (month == 4 || month == 6 || month == 9 || month == 11)) {
        return false;
    }
    // check for February (assuming no leap years)
    if (month == 2 && day > 28) {
        return false;
    }
    return true;
}