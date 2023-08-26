#ifndef MOTORBIKE_H
#define MOTORBIKE_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Motorbike{
    private:
        // Member owner;
        // vector<Member> requesters;   // vector of members requesting to rent
        string motorId, model, color, engineSize, transmissionMode, description;
        unsigned int yearMade;
        double consumptionPoint, minRenterRating, ratingScore;
        bool isAvailable;

    public:
        Motorbike();
        
        // set default attribute values in constructor
        Motorbike(string motorId, string model="None", string color="black", string engineSize="None", string transmissionMode="None", string description="None",
        unsigned int yearMade=2023, double consumptionPoint=0, double minRenterRating=0, double ratingScore=0, bool isAvalable=true);

        ~Motorbike();

        void showInfo();

        void viewRequests();

        void viewReviews(); // view data from MotorbikeReview.txt

        // take the min required renter rating from data & set to minRenterRating
        void listRenterFilter();

        // remove rating filter for renters
        void unlistRenterFilter();

        friend class Member;
};

#endif