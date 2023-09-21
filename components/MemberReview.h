#ifndef MEMBERREVIEW_H
#define MEMBERREVIEW_H
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class MemberReview {
    private: 
    string reviewId, motorId, renterId, comment;
    double rating;
    public:
    MemberReview(string reviewId, string motorId, string renterId, double rating, string comment);

    static MemberReview createObject(string line);

    string formatForSaving();

    void showInfo();

    friend class UserInterface;
};  

#endif