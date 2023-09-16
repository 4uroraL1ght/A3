#ifndef MOTORBIKE_H
#define MOTORBIKE_H
#include <iostream>
#include <string>
#include <vector>
#include "../user/Member.h"
#include "../action/Rental.h"
#include "../action/FileController.h"

using namespace std;

class Member;   // forward declaration
class Rental;

class Motorbike{
    private:
        // Member* owner = nullptr;
        string motorId, ownerId, model, color, engineSize, transmissionMode, description, city;
        unsigned int yearMade;
        double consumingPoints, minRenterRating, ratingScore;
        bool isAvailable;
        // vector<Rental> rentals;    // store both accepted and requesting rentals

    public:
        Motorbike();
        
        // set default attribute values in constructor
        Motorbike(string motorId = "", string ownerId = "", string model = "None", string color = "black", string engineSize = "None", string transmissionMode = "None", string description = "None",
        unsigned int yearMade = 2023, double consumingPoints = 1, string city = "Sai Gon", bool isAvailable = false, double minRenterRating = 0, double ratingScore = 0);

        ~Motorbike();

        string toString();

        void showInfo();

        void showInfoDetail();

        static Motorbike createObject(string line);

        // request to rent the motorbike, takes in day and month of begin and end dates of renting
        void requestToRent(Member* renter);

        void viewRequests();

        void viewReviews(); // view data from MotorbikeReview.txt

        bool changeCurrentSettings();

        // take the min required renter rating from data & set to minRenterRating
        void listMotorbike();

        // remove rating filter for renters
        void unlistMotorbike();

        friend class Member;
        friend class Rental;
        friend class AdminInterface;
        friend class UserInterface;
};

#endif