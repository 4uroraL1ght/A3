#ifndef ADMININTERFACE_H
#define ADMININTERFACE_H

#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"
#include "../user/Member.h"
#include "../user/Admin.h"
#include "../action/Rental.h"

using namespace std;

class AdminInterface{
    private:
        vector<Motorbike> motorbikes;
        vector<Member> members;
        vector<Rental> rentals;
    public:
        
        AdminInterface();

        void loadRentalComponents();

        void saveToFiles();

        int displayAdminMenu();

        void displayMembers();

        void displayMotorbikes();

        void displayRentals();

        void runInterface();
};

#endif