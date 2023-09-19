#include <iostream>
#include "Admin.h"
using namespace std;

Admin::Admin(){}

// read from file to check admin login information and return bool value
bool Admin::logging(){
    cout << "Enter your Admin ID: "; cin >> adminID;
    cout << "Enter your Password: "; cin >> password;

    ifstream admindata("data/Admin.txt");

    if (!admindata.is_open()){  // check file open
        cout << "Unable to open file";
        return false;
    }
    getline(admindata, admincheck);
    getline(admindata, passcheck);
    admindata.close();  // close file

    if(admincheck == adminID && passcheck == password) {
        cout << "Login successful! " << endl;
        return true;
    } else {
        cout << "Login failed. Please try again." << endl;
        return false;
    }
}