#ifndef REVIEW_H
#define REVIEW_H
#include <iostream>
#include <string>
using namespace std;

class MotorbikeReview {
    private: 
    string comment, reviewId, motorId, renterId;
    double ratingScore;
    public:
    MotorbikeReview(string reviewId, string motorId, string renterId, double ratingScore, string comment);
    string formatForSaving();
    static MotorbikeReview createObject(string line);

    void showInfo();


    friend class Motorbike;
    friend class Member;
    friend class UserInterface;
};

#endif