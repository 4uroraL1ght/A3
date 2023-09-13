#include <iostream>
#include <string>
#include <vector>
#include "components/Motorbike.h"
#include "action/FileController.h"
#include "interface/AdminInterface.h"
#include "interface/UserInterface.h"
using namespace std;


int main(int argc, char const *argv[])
{
    // testing
    AdminInterface admin;
    for (int i = 0; i < admin.motorbikes.size(); i++){
        admin.motorbikes[i].showInfo();
        // cout << admin.motorbikes[i].toString();
    }

    for (int i = 0; i < admin.members.size(); i++){
        admin.members[i].showInfo();
    }

    UserInterface user;
    user.runInterface();

    // admin.motorbikes.push_back(Motorbike("M004", "MB004", "MotorBikee", "white", "2000", "automatic", "New motorbike", 2022, 8, "Sai Gon", true, 3, 2));
    // admin.motorbikes[3].showInfo();
    // cout << admin.motorbikes[3].toString();

    // admin.saveToFiles();

    return 0;
}