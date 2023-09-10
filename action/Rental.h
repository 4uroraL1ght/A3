#ifndef RENTAL_H
#define RENTAL_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include "../components/Motorbike.h"
#include "../user/Member.h"

using namespace std;

class Rental {
    private:
        string rentalId;
        Member owner, renter;
        tm beginDate, endDate;      // data type for storing date info
        bool isAccepted;

    public:
        Rental(string rentalId = "", Member owner, Member renter, int bday, int bmonth, int eday, int emonth, bool isAccepted = false);

        void showInfo();

        // give access for other classes
        friend class Motorbike;
        friend class Member;
};

#endif