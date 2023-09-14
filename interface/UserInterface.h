#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"
#include "../user/Member.h"

using namespace std;

class UserInterface{
    public:
        vector<Motorbike> motorbikes;
        vector<Member> members;
        
        UserInterface();

        void saveToFiles();

        Member* loginMember(int *userType, bool *isLoggedIn);

        int displayMemberMenu();

        int displayMemMenuNoMotorbike();

        void addNewMotorbike(Member* member);

        Member* findMemberById(string memId);

        void searchSuitableMotorbikes(Member* mem);

        void displayMotorbikes(vector<Motorbike> suitableMtb, Member* renter);

        void runInterface();
};

#endif