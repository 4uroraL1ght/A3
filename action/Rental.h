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

class Member;   // forward declaration
class Motorbike;

class Rental {
    private:
        string rentalId;
        Motorbike* motorbike;
        Member* renter;
        tm beginDate, endDate;      // data type for storing date info
        bool isAccepted;

    public:
        Rental(string rentalId = "", Motorbike* motorbike = nullptr, Member* renter = nullptr, 
        int bday = 1, int bmonth = 10, int eday = 5, int emonth = 10, bool isAccepted = false);

        void showInfo();

        // give access for other classes
        friend class Motorbike;
        friend class Member;
};

#endif