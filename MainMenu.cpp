#include <iostream>
#include <string>
#include <vector>
#include "components/Motorbike.h"
#include "action/FileController.h"
#include "interface/AdminInterface.h"

using namespace std;


int main(int argc, char const *argv[])
{
    // testing
    AdminInterface admin;
    for (int i = 0; i < admin.motorbikes.size(); i++){
        admin.motorbikes[i].showInfo();
        cout << admin.motorbikes[i].toString();
    }
    admin.motorbikes.push_back(Motorbike("M004", "MotorBikee", "white", "2000", "automatic", "New motorbike", 2022, 8, true, 3, 2));
    admin.motorbikes[3].showInfo();
    cout << admin.motorbikes[3].toString();

    admin.safeToFiles();

    return 0;
}