#ifndef ADMININTERFACE_H
#define ADMININTERFACE_H

#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"
#include "../user/Member.h"

using namespace std;

class AdminInterface{
    public:
        vector<Motorbike> motorbikes;
        vector<Member> members;
        
        AdminInterface();

        void saveToFiles();

        int displayAdminMenu();
};

#endif