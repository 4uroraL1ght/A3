#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Admin{
    private:
        string adminID, password, admincheck, passcheck;
    public:
        // default constructor for Admin object
        Admin();

        // logging function for admin
        bool logging();

};

#endif