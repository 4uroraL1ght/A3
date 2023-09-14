#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Rental.h"

using namespace std;

Rental::Rental(string rentalId, Motorbike* motorbike, Member* renter, int bday, int bmonth, int eday, int emonth, bool isAccepted)
: rentalId(rentalId), motorbike(motorbike), renter(renter), isAccepted(isAccepted) {
    // initialize day and month in begin and end dates
    beginDate.tm_mday = bday;
    beginDate.tm_mon = bmonth;
    endDate.tm_mday = eday;
    endDate.tm_mon = emonth;
}

// show information of rental
void Rental::showInfo(){
    cout << "\n------ Rental Information ------\n";
    cout << "Rental ID: " << rentalId << endl;
    cout << "Owner ID: " << motorbike->ownerId << endl;
    cout << "Renter: " << renter->fullName << "\tID: " << renter->userId << endl;
    cout << "Begin Date: " << beginDate.tm_mday << '/' << beginDate.tm_mon << "/2023" << endl;
    cout << "End Date: " << endDate.tm_mday << '/' << endDate.tm_mon << "/2023" << endl;
    cout << "Current Status: " << (isAccepted ? "Accepted" : "Processing") << endl;
    cout << "-------------------------------\n";
}