#include <iostream>
#include <vector>
#include <sstream>
#include "MotorbikeReview.h"

using namespace std;

MotorbikeReview::MotorbikeReview(string reviewId, string motorId, string renterId, double ratingScore, string comment) 
: reviewId(reviewId), motorId(motorId), renterId(renterId), ratingScore(ratingScore), comment(comment){}

// format for saving into file
string MotorbikeReview::formatForSaving() {
    return reviewId + "," + motorId + "," + renterId + "," + to_string(ratingScore) + "," + comment + '\n';
}

MotorbikeReview MotorbikeReview::createObject(string line) {
    stringstream ss(line);
    string reviewId, motorId, renterId, comment, temp;
    double ratingScore;
    getline(ss, reviewId, ',');
    getline(ss, motorId, ',');
    getline(ss, renterId, ',');
    getline(ss, temp, ',');
    ratingScore = stod(temp);
    getline(ss, comment, ',');
    return MotorbikeReview(reviewId, motorId, renterId, ratingScore, comment);
}

void MotorbikeReview::showInfo(){
    cout << "Review ID: " << reviewId << "; Motorbike ID: " << motorId << "; Renter ID: " << renterId
    << "; Rating score: " << ratingScore << "; Comment: " << comment << endl;
}