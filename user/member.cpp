#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool logging_member(){
    string username, password, usercheck, passcheck;

    cout << "Enter your Username: "; cin >> username;
    cout << "Enter your Password: "; cin >> password;

    ifstream admindata("../data/Member.txt");
    getline(admindata, usercheck);
    getline(admindata, passcheck);

    if(usercheck == username && passcheck == password){
        return true;
    }else{
        return false;
    }
}

int main(){
    bool login = logging_member();
    if(!login){
        cout << "Login failed please try again " << endl;
    }else{
        cout << "Login successful! " << endl;
    }
}