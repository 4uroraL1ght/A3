#ifndef ADMININTERFACE_H
#define ADMININTERFACE_H

#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"

using namespace std;

class AdminInterface{
    public:
        vector<Motorbike> motorbikes;
        
        AdminInterface();
};

#endif