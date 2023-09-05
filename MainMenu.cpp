#include <iostream>
#include <string>
#include <vector>
#include "components/Motorbike.h"
#include "action/FileController.h"
#include "interface/AdminInterface.h"

using namespace std;


int main(int argc, char const *argv[])
{
    AdminInterface admin;
    for (int i = 0; i < admin.motorbikes.size(); i++){
        admin.motorbikes[i].showInfo();
    }

    return 0;
}