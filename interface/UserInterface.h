#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"
#include "../user/Member.h"
#include "../action/Rental.h"
#include "../components/MotorbikeReview.h"

using namespace std;

class UserInterface{
    public:
        vector<Motorbike> motorbikes;
        vector<Member> members;
        vector<Rental> rentals;
        vector<MotorbikeReview> motorbikeReviews; 
        
        UserInterface();

        void saveToFiles();

        void loadRentalComponents();

        Member* loginMember(int *userType, bool *isLoggedIn);

        int displayMemberMenu();

        int displayMemMenuNoMotorbike();

        void addNewMotorbike(Member* member);

        Member* findMemberById(string memId);

        void searchSuitableMotorbikes(Member* mem);

        void displayMotorbikes(vector<Motorbike>& suitableMtb, Member* renter);

        int displayRequestOptions();

        void displayRequests(Member* owner);

        vector<Rental> findRentalHistory(Member *renter);
        void viewHistory(Member *renter);
        int displayReviewAndRatingOptions();
        void leaveCommentAndRating(vector<Rental> rentalHistory);

        void runInterface();
};

#endif