#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../user/Member.h"
#include "../components/Motorbike.h"
#include "../interface/UserInterface.h"

using namespace std;

Member::Member(string userId, string username, string password, string fullName, string phoneNumber, string idType, string passportNum,
        string driverLicenseNum, string expiryDate, string city, double creditPoints, double renterRating, bool isRenting)
        : userId(userId), username(username), password(password), fullName(fullName), phoneNumber(phoneNumber), idType(idType), passportNum(passportNum),
        driverLicenseNum(driverLicenseNum), expiryDate(expiryDate), city(city), creditPoints(creditPoints), renterRating(renterRating), isRenting(isRenting){}

// take in a line of data and return Member object
Member Member::createObject(string line){
    stringstream ss(line);
    string temp, id, username, pw, fullName, phone, idType, ppNum, licenseNum, expiryDate, city;
    double credit, rating;
    bool isRenting;
    getline(ss, id, ',');
    getline(ss, username, ',');
    getline(ss, pw, ',');
    getline(ss, fullName, ',');
    getline(ss, phone, ',');
    getline(ss, idType, ',');
    getline(ss, ppNum, ',');
    getline(ss, licenseNum, ',');
    getline(ss, expiryDate, ',');
    getline(ss, city, ',');
    getline(ss, temp, ',');
    credit = stod(temp);
    getline(ss, temp, ',');
    rating = stod(temp);
    getline(ss, temp, ',');
    isRenting = stoi(temp);
    return Member(id, username, pw, fullName, phone, idType, ppNum, licenseNum, expiryDate, city, credit, rating, isRenting);
}

// show info (used by member)
    void Member::showMyInfo() {
        ifstream memberdata("data/Member.txt");

        if (!memberdata.is_open()) {
            cout << "Unable to display" << endl;
            return;
        }

        string line;

        while (getline(memberdata, line)) {
            // Use stringstream to split the line by comma
            stringstream ss(line);
            string userIdCheck, usernameCheck, passwordCheck;

            if (getline(ss, userIdCheck, ',') && getline(ss, usernameCheck, ',') && getline(ss, passwordCheck, ',')) {
                if (userIdCheck == userId) {
                    // Display the information of the member whose userId matches the logged-in user.
                    cout << "--- Your Information ---" << endl;
                    cout << "User ID: " << userId << endl;
                    cout << "Username: " << usernameCheck << endl;
                    cout << "Full name: " << fullName << endl;
                    cout << "Phone: " << phoneNumber << endl;
                    cout << "ID Type: " << idType << endl;
                    cout << "ID Number: " << passportNum << endl;
                    cout << "Driver's License Number: " << driverLicenseNum << endl;
                    cout << "Expiry: " << expiryDate << endl;
                    cout << "City: " << city << endl;
                    cout << "Credit Points: " << creditPoints << endl;
                    cout << "Rating Score: " << renterRating << endl;
                    break;
                }
            }
        }

        memberdata.close();
    }

// return string line format to save into txt file
string Member::formatForSaving(){
    return userId + ',' + username + ',' + password + ',' + fullName + ',' + phoneNumber + ',' + 
    idType + passportNum + ',' + driverLicenseNum + ',' + expiryDate + ',' + city + ',' + 
    to_string(creditPoints) + ',' + to_string(renterRating) + ',' + to_string(isRenting) + '\n';
}

// show info in 1 line (used by admin to easily view list of all members)
void Member::showInfo(){
    cout << "User ID: " << userId << "; " << "Full name: " << fullName << "; Phone: " << phoneNumber << "; ID Type: " << idType
    << "; ID Number: " << passportNum << ";  Driver's License Number: " << driverLicenseNum << 
    "; Expiry: " << expiryDate << "; " << city << "; Credit Points: " << creditPoints << "; Rating Score: " << renterRating << endl;
}

void Member::findMyMotorbike(vector<Motorbike>& motorbikes){
    for (auto& mt : motorbikes){
        if (userId == mt.ownerId){
            this->motorbike = &mt;
            return;
        }
    }
    this->motorbike = nullptr;
}
