#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"
#include "UserInterface.h"

#define MOTOR_FILE "data/Motorbike.txt"
#define MEMBER_FILE "data/Member.txt"
#define RENTAL_FILE "data/Rental.txt"
#define MOTOR_REV_FILE "data/MotorbikeReview.txt"

using namespace std;

UserInterface::UserInterface()
{
    this->motorbikes = FileController::loadObjects(MOTOR_FILE, Motorbike::createObject);
    this->members = FileController::loadObjects(MEMBER_FILE, Member::createObject);
    this->rentals = FileController::loadObjects(RENTAL_FILE, Rental::createObject);
    this->motorbikeReviews = FileController::loadObjects(MOTOR_REV_FILE, MotorbikeReview::createObject);
    loadRentalComponents();
}

void UserInterface::loadRentalComponents()
{
    for (Rental &r : rentals)
    {
        r.loadComponents(motorbikes, members);
    }
}

// save all data (vectors of objects) back into files
void UserInterface::saveToFiles()
{
    FileController::writeObjects(MOTOR_FILE, motorbikes);
    FileController::writeObjects(MEMBER_FILE, members);
    FileController::writeObjects(RENTAL_FILE, rentals);
    FileController::writeObjects(MOTOR_REV_FILE, motorbikeReviews);
}

// find and return the right member from members vector
Member *UserInterface::loginMember(int *userType, bool *isLoggedIn)
{
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    for (Member &mem : members)
    {
        if (mem.username == username && mem.password == password)
        {
            cout << "Successfully logged in!\n";
            *isLoggedIn = true;
            return &mem;
        }
    }
    cout << "Member not found. Do you want to try again? (0.No  1.Yes)\n";
    cout << "Enter your choice: ";
    cin >> *userType;
    return nullptr;
}

// Functions to display member menu after successful login
int UserInterface::displayMemberMenu()
{
    int choice;
    cout << "This is your menu:\n";
    cout << "0. Exit\n";
    cout << "1. View your personal information\n";
    cout << "2. View your motorbike's information\n";
    cout << "3. Search suitable motorbikes for rental\n";
    cout << "4. List your motorbike\n";
    cout << "5. Unlist your motorbike\n";
    cout << "6. View requests\n";
    cout << "7. View history\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// function to find a member using member's id
Member *UserInterface::findMemberById(string memId)
{
    for (Member &mem : members)
    {
        if (mem.userId == memId)
        {
            return &mem;
        }
    }
    cout << "No member found!\n";
    return nullptr;
}

// display menu for members who have no motorbike
int UserInterface::displayMemMenuNoMotorbike()
{
    int choice;
    cout << "This is your menu:\n";
    cout << "0. Exit\n";
    cout << "1. View your personal information\n";
    cout << "2. Add a new motorbike\n";
    cout << "3. Search suitable motorbikes for rental\n";
    cout << "4. View history\n";
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice >= 0 && choice <= 4)
    {
        return choice;
    }
    return -1;
}

void UserInterface::addNewMotorbike(Member *member)
{
    cout << "You haven't added a motorbike yet.\n";
    cout << "Do you want to add one? (0.No  1.Yes)\n";
    int createMotorbike;
    cout << "Enter your choice: ";
    cin >> createMotorbike;
    string motorId, model, color, engine, transmission, description;
    unsigned int year;
    switch (createMotorbike)
    {
    case 0:
        cout << "Bringing you back...\n";
        break;
    case 1:
        cout << "-- Adding a new motorbike --\n";
        cout << "* Please enter these following information of your motorbike *\n";
        cout << "Model: ";
        getline(cin >> ws, model);
        cout << "Color: ";
        getline(cin >> ws, color);
        cout << "Engine size: ";
        getline(cin >> ws, engine);
        cout << "Transmission mode: ";
        getline(cin >> ws, transmission);
        cout << "Description: ";
        getline(cin >> ws, description);
        cout << "Year made: ";
        cin >> year;
        // create new motorbike
        motorId = FileController::generateUniqueId(motorbikes.back().motorId, "M", 1);
        motorbikes.push_back(Motorbike(motorId, member->userId, model, color, engine, transmission,
                                       description, year, 1, member->city, false, 0, 0)); // add new motorbike to the vector
        member->motorbike = &motorbikes.back();                                           // assign for the member's motorbike
        member->motorbike->showInfoDetail();
        break;
    default:
        cout << "Invalid choice!\n";
        break;
    }
}

// function to display motorbike vector after searching
void UserInterface::displayMotorbikes(vector<Motorbike> &suitableMtb, Member *renter)
{
    for (int i = 0; i < suitableMtb.size(); i++)
    {
        cout << i + 1 << ". ";
        suitableMtb[i].showInfo();
    }

    int userType = 0;
    cout << "Please choose your next move:\n";
    cout << "0. Exit\n1. View detail motorbike\n";
    cout << "Enter your choice: ";
    cin >> userType;
    switch (userType)
    {
    case 0:
        break;
    case 1:
        cout << "Enter the number of motorbike to view: ";
        cin >> userType;
        if (userType > 0 && (userType < suitableMtb.size() + 1))
        {
            suitableMtb[userType - 1].showInfoDetail();
            cout << "Rent this motorbike now? ( 0.No  1.Yes )\n";
            cout << "Enter your choice: ";
            cin >> userType;
            if (userType == 0)
                return;
            else if (userType == 1)
            {
                if (renter->isRenting)
                { // if the renter has already rented a motorbike
                    cout << "You have rented a motorbike and cannot rent more!\n";
                    cout << "Bringing you back...\n";
                    return;
                }
                // call function to create new rental
                Rental *newRental = suitableMtb[userType - 1].requestToRent(renter, rentals.back().rentalId);
                rentals.push_back(*newRental);
                rentals.back().showInfo(); // add new rental to the vector<Rental>
            }
            else
            {
                cout << "Invalid choice!\n";
                return;
            }
        }
        break;
    default:
        cout << "Invalid choice!\n";
        break;
    }
}

// search for motorbikes that suitable with the member
void UserInterface::searchSuitableMotorbikes(Member *member)
{
    vector<Motorbike> suitableMotorbikes;
    for (Motorbike mt : motorbikes)
    { // if 1 condition does not satisfied -> skip turn
        if (mt.ownerId == member->userId)
            continue;
        else if (!mt.isAvailable)
            continue;
        else if (mt.minRenterRating > member->renterRating)
            continue;
        else if (mt.city != member->city)
            continue;
        suitableMotorbikes.push_back(mt);
    }
    if (suitableMotorbikes.size() == 0)
    { // if the counter unchange
        cout << "There's no suitable motorbike available!\n";
    }
    else // display the motorbikes found
        displayMotorbikes(suitableMotorbikes, member);
}

// display request's options and take the user's choice
int UserInterface::displayRequestOptions()
{
    int userChoice;
    cout << "Please choose your next move:\n";
    cout << "0. Exit\n1. Accept a request\n";
    cout << "Enter your choice: ";
    cin >> userChoice;
    switch (userChoice)
    {
    case 0:
        return userChoice;
    case 1:
        cout << "Please choose the request number that you want to accept: ";
        cin >> userChoice;
        return userChoice; // return the request number to accept
        break;
    default:
        cout << "Invalid choice!\n";
        return 0;
        break;
    }
}

// find and display all requests of member's motorbike
void UserInterface::displayRequests(Member *owner)
{
    cout << "----- Requests of Motorbike " << owner->motorbike->motorId << " -----\n";
    int count = 0;
    for (Rental &rt : rentals)
    {
        if (rt.motorId == owner->motorbike->motorId && rt.status == "requested")
        {
            cout << count + 1 << ". ";
            rt.showInfoDetail();
            count++;
        }
    }
    if (count == 0)
    { // if the counter unchanged -> no requests
        cout << "There are no requests for your motorbike!\n";
        return;
    }
    int requestAccept = displayRequestOptions();
    if (requestAccept == 0)
        return;
    else if (requestAccept > count)
    {
        cout << "Invalid choice!\n";
        return;
    }
    else // if the choice is valid -> accept the request
        rentals[requestAccept - 1].acceptRequest();
}

// find and return a vector contain renting history of a member
vector<Rental> UserInterface::findRentalHistory(Member *renter)
{

    vector<Rental> thisMemberPastRentals;
    for (Rental r : rentals)
    {

        if (renter->userId == r.renterId && r.status == "completed")
        {
            thisMemberPastRentals.push_back(r);
        }
    }

    return thisMemberPastRentals;
}

void UserInterface::leaveCommentAndRating(vector<Rental> rentalHistory) {
    int userChoice = displayReviewAndRatingOptions();
    switch(userChoice) {
        case 0:
        return;
        default:
        string comment; double rating;
    cout << "----- Comment and Rating of Motorbike " << rentalHistory[userChoice - 1].motorbike->model << endl;
    cout << "Your review on the motorbike: ";
    getline(cin >> ws, comment);
    cout << "Rate the motorbike: ";
    //cin.ignore(1, '\n');
    // getline(cin, rating);
    cin >> rating;
    
    string reviewId = FileController::generateUniqueId(motorbikeReviews.back().reviewId, "MRV", 3);
    string motorId = rentalHistory[userChoice - 1].motorId;
    string renterId = rentalHistory[userChoice - 1].renterId;
    motorbikeReviews.push_back(MotorbikeReview(reviewId, motorId, renterId, rating, comment));
    cout << "Thank you for your review\n";
    return;
    }
}

void UserInterface::viewHistory(Member *renter)
{
    vector<Rental> rentalHistory = UserInterface::findRentalHistory(renter);

    for (Rental r : rentalHistory)
    {
        for (Member rt : members)
        {
            if (r.renterId == rt.userId)
            {
                r.renter = &rt;
            }
        }
        for (Motorbike m : motorbikes)
        {
            if (r.motorId == m.motorId)
            {
                r.motorbike = &m;
            }
        }
    }
    if (rentalHistory.size() == 0) {
        cout << "No renting history\n";
        return;
    } 
    for (int i=0; i < rentalHistory.size(); i++){
        cout << i+1 << ". ";
        rentalHistory[i].showInfo();
    }
    leaveCommentAndRating(rentalHistory);
}

// function to show choice to leave comment or exit
    int UserInterface::displayReviewAndRatingOptions() {
        int userChoice;
        cout << "Please choose your next move: \n";
        cout << "0.Exit\n1.Review and Rate your experience\n";
        cout << "Enter your choice: ";
        cin >> userChoice;
        switch (userChoice) {
            case 0:
            return userChoice;
            case 1:
            cout << "Please choose the rental that you want to review: ";
            cin >> userChoice; // return the rental that user want to review
            return userChoice;
            break;
            default:
            cout << "Invalid choice!\n";
            return 0;
            break;            
        } 
    }


// main function for running UserInterface
void UserInterface::runInterface()
{
    int userType = 1;
    bool isLoggedIn = false;
    Member *loggedInMem = nullptr;

    // login before creating Member object
    switch (userType)
    {
    case 0:
        cout << "Exiting Member interface...\n";
        break;
    case 1:
        do
        {
            loggedInMem = loginMember(&userType, &isLoggedIn);
            if (userType == 0)
                break;
        } while (loggedInMem == nullptr);
        break;
    default:
        cout << "Invalid choice!\n";
        break;
    }

    // after member logged in
    while (isLoggedIn)
    {
        // load member's motorbike by searching from vector motorbikes
        loggedInMem->findMyMotorbike(motorbikes);
        bool hasMotorbike = (loggedInMem->motorbike != nullptr);

        if (hasMotorbike)
        { // if member has a motorbike
            userType = displayMemberMenu();
        }
        else // if the member has no motorbike, display differently
            userType = displayMemMenuNoMotorbike();

        switch (userType)
        {
        case 0:
            isLoggedIn = false;
            cout << "Logging you out...\n";
            break;
        case 1: // view personal info
            break;
        case 2: // view motorbike info
            if (hasMotorbike)
            {
                loggedInMem->motorbike->showInfoDetail();
            }
            else
            {
                addNewMotorbike(loggedInMem);
            }
            break;
        case 3: // search suitable motorbikes for rental
            searchSuitableMotorbikes(loggedInMem);
            break;
        case 4: // list your motorbike
            loggedInMem->motorbike->listMotorbike();
            break;
        case 5: // unlist your motorbike
            loggedInMem->motorbike->unlistMotorbike();
            break;
        case 6: // view requests
            if (loggedInMem->motorbike->isAvailable)
            { // if the motorbike is listed
                displayRequests(loggedInMem);
            }
            else
                cout << "You have unlisted your motorbike.\n";
            break;
        case 7: // view history
            viewHistory(loggedInMem);
            break;
        default:
            cout << "Invalid choice. Please try again!\n";
            break;
        }
    }
    saveToFiles(); // saving all data to files
}