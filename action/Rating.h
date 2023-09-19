#ifndef RATING_H
#define RATING_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../components/Motorbike.h"
#include "../user/Member.h"
#include "FileController.h"

using namespace std;

class Member;
class Motorbike;

class Rating {
    private:
        int score;
        string comments;
        Motorbike* motorId = nullptr;
        Motorbike* ownerId = nullptr;

    public:
        Rating();

        static Rating createObject(string line);

        bool loadComponents(vector<Motorbike>& motorbikes, vector<Member>& members);

        // ...

        friend class Motorbike;
        friend class Member;
        friend class UserInterface;
};

#endif