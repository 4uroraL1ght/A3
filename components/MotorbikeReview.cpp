#include <iostream>
#include <vector>
#include <sstream>
#include "MotorbikeReview.h"

using namespace std;

MotorbikeReview::MotorbikeReview(string reviewId, string motorId, string renterId, double ratingScore, string comment) : comment(comment), ratingScore(ratingScore),
    motorId(motorId), renterId(renterId), reviewId(reviewId) {}

// format for saving into file
string MotorbikeReview::formatForSaving() {
    return reviewId + "," + motorId + "," + renterId + "," + std::to_string(ratingScore) + "," + comment;
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