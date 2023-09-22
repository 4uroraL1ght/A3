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
    private:
        vector<Motorbike> motorbikes;
        vector<Member> members;
        vector<Rental> rentals;
        vector<MotorbikeReview> motorbikeReviews; 
        vector<MemberReview> memberReviews;
    public:
        UserInterface();

        void saveToFiles();

        void loadRentalComponents();

        Member* loginMember(int *userType, bool *isLoggedIn);

        int displayMemberMenu();

        int displayMemMenuNoMotorbike();

        Member *findMemberById(string memId);

        void addNewMotorbike(Member* member);

        void searchSuitableMotorbikes(Member* mem);

        void displayMotorbikes(vector<Motorbike>& suitableMtb, Member* renter);

        int displayRequestOptions();

        void displayRequests(Member* owner);

        vector<Rental*> findRentalHistory(Member *renter);

        void viewRentalHistory(Member *renter);

        int displayReviewAndRatingMotorOptions();

        void leaveCommentAndRatingForMotor(vector<Rental*> &rentalHistory);

        void updateMotorbikeRating(string motorId);

        vector<Rental*> findRentingHistory(Member *owner);

        void viewRentingHistory(Member *owner);

        int displayReviewAndRatingRenterOptions();

        void leaveCommentAndRatingForRenter(vector<Rental*> &rentalHistory);

        void updateRenterRating(string renterId);

        void returnMotorbike(Member *renter);

        void displayMotorbikeReviews(string motorId);

        void displayMemberReviews(string memberId);

        void viewReviewOptions(Member *member);

        void runInterface();
};

#endif