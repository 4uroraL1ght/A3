/* Acknowledgment:
1. https://en.cppreference.com/w/cpp/chrono 
2. https://cplusplus.com/reference/ */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Rental.h"

using namespace std;

Rental::Rental(string rentalId, string motorId, string renterId, int bday, int bmonth, int duration, string status, bool ownerRated, bool renterRated)
: rentalId(rentalId), motorId(motorId), renterId(renterId), duration(duration), status(status), ownerRated(ownerRated), renterRated(renterRated) {
    // initialize day and month in begin and end dates
    beginDate.tm_mday = bday;
    beginDate.tm_mon = bmonth;
    beginDate.tm_year = 2023 - 1900;
    calculateEndDate();
}

// static function to create and return new Rental object
Rental Rental::createObject(string line){
    stringstream ss(line);
    string rentalId, motorId, renterId, status, date, temp;
    int bday, bmonth, eday, emonth, duration;
    bool ownerRated, renterRated;
    getline(ss, rentalId, ',');
    getline(ss, motorId, ',');
    getline(ss, renterId, ',');
    getline(ss, temp, ','); bday = stoi(temp);
    getline(ss, temp, ','); bmonth = stoi(temp);
    getline(ss, temp, ','); duration = stoi(temp);
    // eday = stoi(temp);
    // getline(ss, temp, ','); emonth = stoi(temp);
    getline(ss, status, ',');
    getline(ss, temp, ',');
    ownerRated = stoi(temp);
    getline(ss, temp, ',');
    renterRated = stoi(temp);

    return Rental(rentalId, motorId, renterId, bday, bmonth, duration, status, ownerRated, renterRated);
}

// function to format the rental for saving into txt file
string Rental::formatForSaving(){
    return rentalId + ',' + motorId + ',' + renter->userId + ',' + 
    to_string(beginDate.tm_mday) + ',' + to_string(beginDate.tm_mon) + "," +
    to_string(duration) + ',' +
    status + ',' + to_string(ownerRated) + ',' + to_string(renterRated) + '\n';
}

// function to find and assign the appropriate objects Motorbike and Member (renter) for the rental
bool Rental::loadComponents(vector<Motorbike> &motorbikes, vector<Member>& members){
    for (auto& mt : motorbikes){    // find the motorbike's object
        if (this->motorId == mt.motorId){
            this->motorbike = &mt;
        }
    }
    for (auto& rt : members){       // find the renter's object
        if (this->renterId == rt.userId){
            this->renter = &rt;
        }
    }
    if (motorbike == nullptr || renter == nullptr){
        cout << "Rental's information not found!\n";
        return false;
    }
    return true;
}

// show information of rental
void Rental::showInfoDetail(){
    cout << "\n------ Rental Information ------\n";
    cout << "Rental ID: " << rentalId << endl;
    cout << "Owner ID: " << motorbike->ownerId << "\tMotorbike ID: " << motorId << endl;
    cout << "Renter: " << renter->fullName << "\tID: " << renter->userId;
    cout << "\nRenter's rating score: " << renter->renterRating << endl;
    cout << "Begin Date: " << beginDate.tm_mday << '/' << beginDate.tm_mon << "/2023\n";
    cout << "End Date: " << endDate.tm_mday << '/' << endDate.tm_mon << '/' << endDate.tm_year << endl;
    cout << "Renting Duration: " << duration << " days\n";
    cout << "Total of consuming points: " << getTotalConsumingPoints() << endl;
    cout << "Current Status: " << status << endl;
    cout << "-------------------------------\n";
}

// show info in 1 line for admin
void Rental::showInfo(){
    cout << "ID: " << rentalId << ";  Onwer ID: " << motorbike->ownerId << ";  Motorbike ID: " << motorId
    << ";  Renter ID: " << renterId << "; Duration: " << duration << " days;  Renting Date: " << beginDate.tm_mday << '/' 
    << beginDate.tm_mon << "/2023 to " << endDate.tm_mday << '/' << endDate.tm_mon << '/' << endDate.tm_year <<
    "/2023;  Total Points: " << getTotalConsumingPoints() << ";  Status: " << status << '\n';
}

// calculate the total consuming points (price) of the rental
double Rental::getTotalConsumingPoints(){
    return duration * this->motorbike->consumingPoints;
}

// check if the renter has enough credit points to pay for the rental
bool Rental::hasEnoughCredit(){
    return (renter->creditPoints >= getTotalConsumingPoints());
}

void Rental::acceptRequest(vector<Rental> &rentals){
    this->status = "accepted";
    this->renter->creditPoints -= getTotalConsumingPoints();     // subtract credit points from the renter
    renter->isRenting = true;     // update that the member is renting a motorbike
    int countReject = 0;
    for (Rental &r : rentals){
        // if other rentals with the same motorbike id and status "requested" -> reject
        if (r.rentalId != this->rentalId && r.motorId == this->motorId && r.status == "requested"){
            r.rejectRequest();
            countReject++;
        }
    }
    cout << "Request ID " << rentalId << " has been accepted.\n";
    cout << countReject << " Request(s) have been rejected.\n";
}

void Rental::rejectRequest(){
    this->status = "rejected";
}

// calculate and assign the end date of renting
void Rental::calculateEndDate() {
    // create int array to store days in each month (not include leap years)
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // store begin date in temp variable to calculate the end date
    tm endDateTemp = beginDate;
    endDateTemp.tm_mday += duration; // add the duration to begin day

    // handle rollover of days
    while (endDateTemp.tm_mday > daysInMonth[endDateTemp.tm_mon]) {
        endDateTemp.tm_mday -= daysInMonth[endDateTemp.tm_mon];
        endDateTemp.tm_mon++;
        if (endDateTemp.tm_mon == 12) { // switch to the next year
            endDateTemp.tm_mon = 0;
            endDateTemp.tm_year++;
        }
    }
    endDate = endDateTemp;
}

// compare valid date for renting
bool Rental::isValidRentalDate(){
    // convert to time_t type for comparison
    time_t rentalBegin = mktime(&this->beginDate);
    time_t rentalEnd = mktime(&this->endDate);
    time_t motorBegin = mktime(&motorbike->beginDate);
    time_t motorEnd = mktime(&motorbike->endDate);

    // check if the rental dates fall in available dates of the motorbike
    return (rentalBegin >= motorBegin && rentalEnd <= motorEnd);
}