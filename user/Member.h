#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <string>
#include "../components/Motorbike.h"

using namespace std;

class Motorbike;    // forward declaration

class Member {
    private:
        string userId, username, fullName, phoneNumber, idType, passportNum, driverLicenseNum, expiryDate, city;
        double creditPoints, renterRating;
        Motorbike* motorbike;

    public:
        Member(string userId="", string username="", string fullName="", string phoneNumber="", string idType="", string passportNum="",
        string driverLicenseNum="", string expiryDate="", string city="Sai Gon", double creditPoints=20, double renterRating=0);

        static Member createObject(string line);

        void showInfo();

        friend class Motorbike;
        friend class UserInterface;
};

#endif