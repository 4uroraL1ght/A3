// #include <iostream>
// #include <string>
// #include <vector>
// #include <sstream>
// #include "../action/Rental.h"

// using namespace std;

// Rental::Rental(string rentalId, Member owner, Member renter, int bday, int bmonth, int eday, int emonth, bool isAccepted)
// : rentalId(rentalId), owner(owner), renter(renter), isAccepted(isAccepted) {
//     // initialize day and month in begin and end dates
//     beginDate.tm_mday = bday;
//     beginDate.tm_mon = bmonth;
//     endDate.tm_mday = eday;
//     endDate.tm_mon = emonth;
// }

// // show information of rental
// void Rental::showInfo(){
//     cout << "Rental Information\n";
//     cout << "Rental ID: " << rentalId << endl;
//     // cout << "Owner: " << owner.name << endl;
//     // cout << "Renter: " << renter.name << endl;
//     cout << "Begin Date: " << beginDate.tm_mday << '/' << beginDate.tm_mon << "/2023" << endl;
//     cout << "End Date: " << endDate.tm_mday << '/' << endDate.tm_mon << "/2023" << endl;
//     cout << "Current Status: " << (isAccepted ? "Accepted" : "Processing") << endl;
// }