#include "MemberReview.h"

MemberReview::MemberReview(string reviewId, string motorId, string renterId, double rating, string comment) :
reviewId(reviewId), motorId(motorId), renterId(renterId), rating(rating), comment(comment) {};

MemberReview MemberReview::createObject(string line) {
    stringstream ss(line);
    string reviewId, motorId, renterId, comment, temp;
    double rating;
    getline(ss, reviewId, ',');
    getline(ss, motorId, ',');
    getline(ss, renterId, ',');
    getline(ss, temp, ',');
    rating = stod(temp);
    getline(ss, comment, ',');
    return MemberReview(reviewId, motorId, renterId, rating, comment);
}

string MemberReview::formatForSaving() {
    return reviewId + "," + motorId + "," + renterId + "," + to_string(rating) + "," + comment + '\n';
}