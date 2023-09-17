#ifndef RENTAL_H
#define RENTAL_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include "../components/Motorbike.h"
#include "../user/Member.h"
#include "FileController.h"

using namespace std;

class Member;   // forward declaration
class Motorbike;

class Rental {
    private:
        string rentalId, motorId, renterId;
        Motorbike* motorbike = nullptr;
        Member* renter = nullptr;
        tm beginDate, endDate;          // data type for storing date info
        string status;                  // status of the rental
        double totalConsumingPoints;    // total price (points)
        int duration;                   // counted by days

    public:
        Rental(string rentalId = "", string motorId = "", string renterId = "", int bday = 1, int bmonth = 10, int eday = 5, int emonth = 10, string status = "requested");

        static Rental createObject(string line);

        bool loadComponents(vector<Motorbike>& motorbikes, vector<Member>& members);

        string formatForSaving();

        void showInfoDetail();

        void showInfo();

        bool isOverlapped();    // check if the request's date is overlapped with the listed date

        void acceptRequest();

        void rejectRequest();

        // give access for other classes
        friend class Motorbike;
        friend class Member;
        friend class UserInterface;
};

#endif