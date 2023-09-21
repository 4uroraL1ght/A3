#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"
#include "../user/Member.h"
#include "../action/Rental.h"
#include "../components/MotorbikeReview.h"
#include "../components/MemberReview.h"

using namespace std;

class UserInterface{
    public:
        vector<Motorbike> motorbikes;
        vector<Member> members;
        vector<Rental> rentals;
        vector<MotorbikeReview> motorbikeReviews; 
        vector<MemberReview> memberReviews;
        
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
        void viewRentalHistory(Member *renter);
        int displayReviewAndRatingMotorOptions();
        void leaveCommentAndRatingForMotor(vector<Rental> rentalHistory);

        void updateMotorbikeRating(string motorId);

        vector<Rental> findRentingHistory(Member *owner);
        void viewRentingHistory(Member *owner);
        int displayReviewAndRatingRenterOptions();
        void leaveCommentAndRatingForRenter(vector<Rental> rentalHistory);

        void updateRenterRating(string renterId);
        void returnMotorbike(Member *renter);

        void runInterface();
};

#endif