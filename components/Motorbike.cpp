#include <iostream>
#include <string>
#include <vector>
#include "Motorbike.h"
// #include "user/Member.h"

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
        Motorbike::Motorbike();

        Motorbike::Motorbike(string motorId, string model, string color, string engineSize, string transmissionMode, string description,
        unsigned int yearMade, double consumptionPoint, double minRenterRating, double ratingScore, bool isAvalable)
        : motorId(motorId), model(model), color(color), engineSize(engineSize), transmissionMode(transmissionMode), 
        description(description), yearMade(yearMade), consumptionPoint(consumptionPoint), minRenterRating(minRenterRating), 
        ratingScore(ratingScore), isAvailable(isAvailable){}

        Motorbike::~Motorbike(){}

        void Motorbike::showInfo(){
            cout << "--- Motorbike information ---" << endl;
            cout << "Motorbike ID: " << motorId << "\tOwner's Name: " << "\tOwner ID: " << endl;
            cout << "Model: " << model << "\tColor: " << color << "\nEngine Size: " << engineSize << endl;
            cout << "Transmission Mode: " << transmissionMode << "\tYear Made: " << yearMade << endl;
            cout << "Description: " << description << endl;
            cout << "Consumption Point: " << consumptionPoint << endl;
            cout << "Rating Score: " << ratingScore << "\tAvailability: " << isAvailable << endl;
        }

        void Motorbike::viewRequests(){}

        void Motorbike::viewReviews(){
            // view data from MotorbikeReview.txt
        }

        void Motorbike::listRenterFilter(){
            // take the min required renter rating from data & set to minRenterRating
        }

        void Motorbike::unlistRenterFilter(){
            // remove rating filter for renters
            this->minRenterRating = 0;
        }

        friend class Member;    // allow access private attributes
};