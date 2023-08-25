#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool logging(){
    string adminID, password, admincheck, passcheck;

    cout << "Enter your Admin ID: "; cin >> adminID;
    cout << "Enter your Password: "; cin >> password;

    ifstream admindata("../data/Admin.txt");
    getline(admindata, admincheck);
    getline(admindata, passcheck);

    if(admincheck == adminID && passcheck == password){
        return true;
    }else{
        return false;
    }
}

int main(){
    bool login = logging();
    if(!login){
        cout << "Login failed please try again " << endl;
        return 0;
    }else{
        cout << "Login successful! " << endl;
        return 1;
    }
}