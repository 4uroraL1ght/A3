#ifndef MEMBER_H
#define MEMBER_H
#include <iostream>
#include <string>
#include "../components/Motorbike.h"

using namespace std;

class Motorbike;    // forward declaration

class Member {
    private:
        string userId, username, password, fullName, phoneNumber, idType, passportNum, driverLicenseNum, expiryDate, city;
        double creditPoints, renterRating;
        Motorbike* motorbike;
        bool isRenting;     // to check if the member is currently renting a motorbike or not

    public:
        Member(string userId="", string username="", string password="", string fullName="", string phoneNumber="", string idType="", string passportNum="",
        string driverLicenseNum="", string expiryDate="", string city="Sai Gon", double creditPoints=20, double renterRating=0, bool isRenting = false);

        static Member createObject(string line);

        string formatForSaving();

        void showMyInfo();

        void showInfo();

        void findMyMotorbike(vector<Motorbike>& motorbikes);

        friend class Motorbike;
        friend class Rental;
        friend class UserInterface;
};

#endif