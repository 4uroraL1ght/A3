#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../user/Member.h"
#include "../components/Motorbike.h"
#include "../interface/UserInterface.h"

using namespace std;

Member::Member(string userId, string username, string fullName, string phoneNumber, string idType, string passportNum,
        string driverLicenseNum, string expiryDate, string city, double creditPoints, double renterRating)
        : userId(userId), username(username), fullName(fullName), phoneNumber(phoneNumber), idType(idType), passportNum(passportNum),
        driverLicenseNum(driverLicenseNum), expiryDate(expiryDate), city(city), creditPoints(creditPoints), renterRating(renterRating){}

Member Member::createObject(string line){
    stringstream ss(line);
    string temp, id, username, fullName, phone, idType, ppNum, licenseNum, expiryDate, city;
    double credit, rating;
    getline(ss, id, ',');
    getline(ss, username, ',');
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
    return Member(id, username, fullName, phone, idType, ppNum, licenseNum, expiryDate, city, credit, rating);
}

// show info in 1 line (used by admin to easily view list of all members)
void Member::showInfo(){
    cout << userId << "; " << fullName << "; Phone: " << phoneNumber << "; ID Type: " << idType
    << "; ID Number: " << passportNum << ";  Driver's License Number: " << driverLicenseNum << 
    "; Expiry: " << expiryDate << "; " << city << "; Credit Points: " << creditPoints << "; Rating Score: " << renterRating << endl;
}


/* Previous code */
// bool logging_member(){
//     string username, password, usercheck, passcheck;

//     cout << "Enter your Username: "; cin >> username;
//     cout << "Enter your Password: "; cin >> password;

//     ifstream admindata("../data/Member.txt");
//     getline(admindata, usercheck);
//     getline(admindata, passcheck);

//     if(usercheck == username && passcheck == password){
//         return true;
//     }else{
//         return false;
//     }
// }

// int main(){
//     bool login = logging_member();
//     if(!login){
//         cout << "Login failed please try again " << endl;
//     }else{
//         cout << "Login successful! " << endl;
//     }
// }