#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../components/Motorbike.h"
// #include "user/Member.h"

using namespace std;

        Motorbike::Motorbike(string motorId, string model, string color, string engineSize, string transmissionMode, string description,
        unsigned int yearMade, double consumptionPoint, bool isAvalable, double minRenterRating, double ratingScore)
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
            cout << "Rating Score: " << ratingScore << "\tAvailability: " << boolalpha << isAvailable << endl;
            cout << endl;
        }

        Motorbike Motorbike::createObject(string line){
            stringstream ss(line);
            string temp, motorId, model, color, engineSize, transmissionMode, description;
            double consumptionPoint, minRenterRating=0, ratingScore=0;
            bool isAvailable; unsigned int year;
            getline(ss, motorId, ',');
            getline(ss, model, ',');
            getline(ss, color, ',');
            getline(ss, engineSize, ',');
            getline(ss, transmissionMode, ',');
            getline(ss, description, ',');
            ss >> year;
            ss >> consumptionPoint;
            getline(ss, temp, ',');
            isAvailable = (temp == "true");
            ss >> minRenterRating;
            ss >> ratingScore;
            return Motorbike(motorId, model, color, engineSize, transmissionMode, description,
            year, consumptionPoint, isAvailable, minRenterRating, ratingScore);
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