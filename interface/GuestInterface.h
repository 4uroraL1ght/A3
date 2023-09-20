#ifndef GUESTINTERFACE_H
#define GUESTINTERFACE_H
#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"

using namespace std;

class GuestInterface{
    public:
        vector<Motorbike> motorbikes;

        GuestInterface();
        
        void saveToFiles();

        int displayGuestMenu();

        void displayMotorbikes();

        void registerMember();

        string generateUniqueUserId();

        string generateUniqueMotorId();

        bool runInterface();
        
};

#endif