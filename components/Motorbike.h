#ifndef MOTORBIKE_H
#define MOTORBIKE_H
#include <iostream>
#include <string>
#include <vector>
#include "../components/Motorbike.h"
#include "../user/Member.h"
#include "../action/Rental.h"
#include "../action/FileController.h"

using namespace std;

class Motorbike{
    private:
        // Member owner;
        // vector<Member> requesters;   // vector of members requesting to rent
        string motorId, model, color, engineSize, transmissionMode, description;
        unsigned int yearMade;
        double consumptionPoint, minRenterRating, ratingScore;
        bool isAvailable;
        vector<Rental> rentals;    // store both accepted and requesting rentals

    public:
        Motorbike();
        
        // set default attribute values in constructor
        Motorbike(string motorId, string model="None", string color="black", string engineSize="None", string transmissionMode="None", string description="None",
        unsigned int yearMade=2023, double consumptionPoint=0, bool isAvailable=true, double minRenterRating=0, double ratingScore=0);

        ~Motorbike();

        string toString();

        void showInfo();

        static Motorbike createObject(string line);

        // request to rent the motorbike, takes in day and month of begin and end dates of renting
        void requestToRent(Member renter, int bday, int bmonth, int eday, int emonth);

        void viewRequests();

        void viewReviews(); // view data from MotorbikeReview.txt

        // take the min required renter rating from data & set to minRenterRating
        void listRenterFilter();

        // remove rating filter for renters
        void unlistRenterFilter();

        friend class Member;
};

#endif