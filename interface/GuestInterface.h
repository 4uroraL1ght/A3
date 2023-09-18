#ifndef GUESTINTERFACE_H
#define GUESTINTERFACE_H
#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"

using namespace std;

class GuestInterface{
    public:
        vector<Motorbike> motorbikes;

        void loadRentalComponents();

        int displayGuestMenu();

        void displayMotorbikes();

        void registerMember();

        void runInterface();
        
};

#endif