#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Rental.h"

using namespace std;

Rental::Rental(string rentalId, string motorId, string renterId, int bday, int bmonth, int eday, int emonth, string status, bool ownerRated, bool renterRated)
: rentalId(rentalId), motorId(motorId), renterId(renterId), status(status), ownerRated(ownerRated), renterRated(renterRated) {
    // initialize day and month in begin and end dates
    beginDate.tm_mday = bday;
    beginDate.tm_mon = bmonth;
    endDate.tm_mday = eday;
    endDate.tm_mon = emonth;
}

// static function to create and return new Rental object
Rental Rental::createObject(string line){
    stringstream ss(line);
    string rentalId, motorId, renterId, status, date, temp;
    int bday, bmonth, eday, emonth;
    bool ownerRated, renterRated;
    getline(ss, rentalId, ',');
    getline(ss, motorId, ',');
    getline(ss, renterId, ',');
    getline(ss, temp, ','); bday = stoi(temp);
    getline(ss, temp, ','); bmonth = stoi(temp);
    getline(ss, temp, ','); eday = stoi(temp);
    getline(ss, temp, ','); emonth = stoi(temp);
    getline(ss, status, ',');
    getline(ss, temp, ',');
    ownerRated = stoi(temp);
    getline(ss, temp, ',');
    renterRated = stoi(temp);

    return Rental(rentalId, motorId, renterId, bday, bmonth, eday, emonth, status, ownerRated, renterRated);
}

// function to format the rental for saving into txt file
string Rental::formatForSaving(){
    return rentalId + ',' + motorId + ',' + renter->userId + ',' + 
    to_string(beginDate.tm_mday) + ',' + to_string(beginDate.tm_mon) + "," +
    to_string(endDate.tm_mday) + ',' + to_string(endDate.tm_mon) + ',' + 
    status + ',' + to_string(ownerRated) + ',' + to_string(renterRated) + '\n';
}

// function to find and assign the appropriate objects Motorbike and Member (renter) for the rental
bool Rental::loadComponents(vector<Motorbike>& motorbikes, vector<Member>& members){
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
    cout << "\tRenter's rating score: " << renter->renterRating << endl;
    cout << "Begin Date: " << beginDate.tm_mday << '/' << beginDate.tm_mon << "/2023" << endl;
    cout << "End Date: " << endDate.tm_mday << '/' << endDate.tm_mon << "/2023" << endl;
    cout << "Total of consuming points: " << totalConsumingPoints << endl;    // haven't handled
    cout << "Current Status: " << status << endl;
    cout << "-------------------------------\n";
}

// show info in 1 line for admin
void Rental::showInfo(){
    cout << "ID: " << rentalId << ";  Onwer ID: " << motorbike->ownerId << ";  Motorbike ID: " << motorId
    << ";  Renter ID: " << renterId << ";  Renting Date: " << endDate.tm_mday << '/' << endDate.tm_mon << 
    "/2023 to " << endDate.tm_mday << '/' << endDate.tm_mon << "/2023;  Total Points: " << totalConsumingPoints
    << ";  Status: " << status << '\n';
}

void Rental::acceptRequest(){
    this->status = "accepted";
    this->renter->creditPoints -= totalConsumingPoints;     // subtract credit points from the renter
    renter->isRenting = true;     // update that the member is renting a motorbike
}

void Rental::rejectRequest(){
    this->status = "rejected";
}