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
#define MEM_REV_FILE "data/MemberReview.txt"

using namespace std;

UserInterface::UserInterface(){
    this->motorbikes = FileController::loadObjects(MOTOR_FILE, Motorbike::createObject);
    this->members = FileController::loadObjects(MEMBER_FILE, Member::createObject);
    this->rentals = FileController::loadObjects(RENTAL_FILE, Rental::createObject);
    this->motorbikeReviews = FileController::loadObjects(MOTOR_REV_FILE, MotorbikeReview::createObject);
    this->memberReviews = FileController::loadObjects(MEM_REV_FILE, MemberReview::createObject);
    loadRentalComponents();
}

void UserInterface::loadRentalComponents(){
    for (Rental &r : rentals){
        r.loadComponents(motorbikes, members);
    }
}

// save all data (vectors of objects) back into files
void UserInterface::saveToFiles(){
    FileController::writeObjects(MOTOR_FILE, motorbikes);
    FileController::writeObjects(MEMBER_FILE, members);
    FileController::writeObjects(RENTAL_FILE, rentals);
    FileController::writeObjects(MOTOR_REV_FILE, motorbikeReviews);
    FileController::writeObjects(MEM_REV_FILE, memberReviews);
}

// find and return the right member from members vector
Member *UserInterface::loginMember(int *userType, bool *isLoggedIn){
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
int UserInterface::displayMemberMenu(){
    int choice;
    cout << "\nThis is your menu:\n";
    cout << "0. Exit\n";
    cout << "1. View your personal information\n";
    cout << "2. View your motorbike's information\n";
    cout << "3. Search suitable motorbikes for rental\n";
    cout << "4. List your motorbike\n";
    cout << "5. Unlist your motorbike\n";
    cout << "6. View requests\n";
    cout << "7. View rental history\n";
    cout << "8. View renting history\n";
    cout << "9. Return motorbike\n";
    cout << "10. View the reviews\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// display menu for members who have no motorbike
int UserInterface::displayMemMenuNoMotorbike(){
    int choice;
    cout << "\nThis is your menu:\n";
    cout << "0. Exit\n";
    cout << "1. View your personal information\n";
    cout << "2. Add a new motorbike\n";
    cout << "3. Search suitable motorbikes for rental\n";
    cout << "4. View rentals' history\n";
    cout << "5. Return motorbike\n";
    cout << "6. View the reviews\n"; 
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice >= 0 && choice <= 3) return choice;
    else if (choice == 4) return 7;   // to match the feature's number in MemberMenu
    else if (choice == 5) return 9;
    else if (choice == 6) return 10;

    return -1;
}

// function to find a member using member's id
Member *UserInterface::findMemberById(string memId){
    for (Member &mem : members){
        if (mem.userId == memId){
            return &mem;
        }
    }
    cout << "No member found!\n";
    return nullptr;
}

void UserInterface::addNewMotorbike(Member *member){
    cout << "You haven't added a motorbike yet.\n";
    cout << "Do you want to add one? (0.No  1.Yes)\n";
    int createMotorbike;
    cout << "Enter your choice: ";
    cin >> createMotorbike;
    string motorId, model, color, engine, transmission, description;
    unsigned int year;
    switch (createMotorbike){
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
void UserInterface::displayMotorbikes(vector<Motorbike> &suitableMtb, Member *renter){
    for (int i = 0; i < suitableMtb.size(); i++){
        cout << i + 1 << ". ";
        suitableMtb[i].showInfo();
    }
    int userType = 0;
    cout << "Please choose your next move:\n";
    cout << "0. Exit\n1. View detail motorbike and its reviews\n";
    cout << "Enter your choice: ";
    cin >> userType;
    switch (userType){
        case 0:
            break;
        case 1:
            cout << "Enter the number of motorbike to view: ";
            cin >> userType;
            if (userType > 0 && (userType < suitableMtb.size() + 1)){
                suitableMtb[userType - 1].showInfoDetail();
                // show motorbike's reviews
                cout << "List of reviews for the motorbike:\n";
                int countReviews = 0;
                for (MotorbikeReview &motorRv : motorbikeReviews){
                    if (motorRv.motorId == suitableMtb[userType - 1].motorId){
                        cout << countReviews+1 << ". ";
                        motorRv.showInfo();
                        countReviews++;
                    }
                }
                if (countReviews == 0) cout << "This motorbike has no reviews yet.\n";

                cout << "\nRent this motorbike now? ( 0.No  1.Yes )\n";
                cout << "Enter your choice: ";
                cin >> userType;
                if (userType == 0)
                    return;
                else if (userType == 1){
                    if (renter->isRenting){ 
                        // if the renter has already rented a motorbike
                        cout << "You have rented a motorbike and cannot rent more!\n";
                        cout << "Bringing you back...\n";
                        return;
                    }
                    // call function to create new rental
                    Rental *newRental = suitableMtb[userType - 1].requestToRent(renter, rentals.back().rentalId);
                    if (newRental == nullptr){
                        cout << "Failed to create a request!\n";
                    } else {
                        rentals.push_back(*newRental);
                        rentals.back().showInfoDetail(); // add new rental to the vector<Rental>
                    }
                } else {
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
void UserInterface::searchSuitableMotorbikes(Member *member){
    vector<Motorbike> suitableMotorbikes;
    for (Motorbike mt : motorbikes){ 
        // if 1 condition does not satisfied -> skip turn
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
    if (suitableMotorbikes.size() == 0){ // if the counter unchange
        cout << "There's no suitable motorbike available!\n";
    }
    else // display the motorbikes found
        displayMotorbikes(suitableMotorbikes, member);
}

// display request's options and take the user's choice
int UserInterface::displayRequestOptions(){
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
void UserInterface::displayRequests(Member *owner){
    cout << "----- Requests of Motorbike " << owner->motorbike->motorId << " -----\n";
    int count = 0, requestIndex = 0;
    vector<int> indices;    // store indices of the requests in rentals
    for (Rental &rt : rentals){
        if (rt.motorId == owner->motorbike->motorId && rt.status == "requested"){
            cout << count + 1 << ". ";
            rt.showInfoDetail();
            indices.push_back(requestIndex);
            count++;
        }
        requestIndex++;
    }
    if (count == 0){ // if the counter unchanged -> no requests
        cout << "There are no requests for your motorbike!\n";
        return;
    }
    int requestAccept = displayRequestOptions();
    if (requestAccept == 0)
        return;
    else if (requestAccept > count){
        cout << "Invalid choice!\n";
        return;
    }
    else // if the choice is valid -> accept the request
        rentals[indices[requestAccept-1]].acceptRequest(rentals);
}

// find and return a vector contain renting history of a member
vector<Rental*> UserInterface::findRentalHistory(Member *renter){
    vector<Rental*> thisMemberPastRentals;
    for (Rental &r : rentals){
        if (renter->userId == r.renterId && r.status == "completed"){
            thisMemberPastRentals.push_back(&r);
        }
    }
    return thisMemberPastRentals;
}

void UserInterface::leaveCommentAndRatingForMotor(vector<Rental*> &rentalHistory) {
    int userChoice = displayReviewAndRatingMotorOptions();
    switch(userChoice) {
        case 0:
        return;
        default:
        if (userChoice > rentalHistory.size() || userChoice < 0) {
            cout << "Invalid choice!\n";
            return;
        }
        if (rentalHistory[userChoice - 1]->renterRated) {   // if the renter has rated -> turn back
                cout << "You have rated for this motorbike!\nBringing you back...\n\n";
                return;
        }
        string comment, rating;
        cout << "----- Comment and Rating of Motorbike " << rentalHistory[userChoice - 1]->motorbike->model << "------" << endl;
        cout << "Your review on the motorbike: ";
        getline(cin >> ws, comment);
        cout << "Rate the motorbike: ";
        getline(cin, rating);
        rentalHistory[userChoice-1]->renterRated = true;
        string reviewId;
        if (motorbikeReviews.size() == 0) {
            reviewId = FileController::generateUniqueId("", "MRV", 3);
        } else {
            reviewId = FileController::generateUniqueId(motorbikeReviews.back().reviewId, "MRV", 3);
        }
        string motorId = rentalHistory[userChoice - 1]->motorId;
        string renterId = rentalHistory[userChoice - 1]->renterId;
        motorbikeReviews.push_back(MotorbikeReview(reviewId, motorId, renterId, stod(rating), comment));
        updateMotorbikeRating(motorId);
        cout << "Thank you for your review\n";
        return;
    }
}

void UserInterface::viewRentalHistory(Member *renter){
    vector<Rental*> rentalHistory = UserInterface::findRentalHistory(renter);

    for (Rental *r : rentalHistory){
        for (Member rt : members){
            if (r->renterId == rt.userId){
                *r->renter = rt;
            }
        }
        for (Motorbike m : motorbikes){
            if (r->motorId == m.motorId){
                *r->motorbike = m;
            }
        }
    }
    if (rentalHistory.size() == 0) {
        cout << "No renting history\n";
        return;
    } 
    for (int i = 0; i < rentalHistory.size(); i++){
        cout << i + 1 << ". ";
        rentalHistory[i]->showInfoDetail();
    }
    leaveCommentAndRatingForMotor(rentalHistory);
}

// function to show choice to leave comment or exit
int UserInterface::displayReviewAndRatingMotorOptions() {
    int userChoice;
    cout << "Please choose your next move: \n";
    cout << "0. Exit\n1. Review and Rate your experience\n";
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

// function to update the motorbike rating
void UserInterface::updateMotorbikeRating(string motorId) {
    vector<MotorbikeReview> ratingForMotor;
    double sum = 0;
    for (MotorbikeReview mr : motorbikeReviews) {
        if (mr.motorId == motorId) {
            ratingForMotor.push_back(mr);
        }
    }

    for (MotorbikeReview mr : ratingForMotor) {
        if (mr.motorId == motorId) {
        sum += mr.ratingScore;}
        
    }
    double finalRating = sum / ratingForMotor.size();
    for (Motorbike &m : motorbikes) {
        if (m.motorId == motorId) {
            m.ratingScore = finalRating;
        }
    }
}

// function goes to the rental vector and find all the rental whose motor's owner match with the member's ID and return a vector
vector<Rental*> UserInterface::findRentingHistory(Member *owner) {
    vector<Rental*> pastRentalForeachOwner;
    for (Rental &r : rentals) {
        if (r.motorbike->ownerId == owner->userId && r.status == "completed") {
            pastRentalForeachOwner.push_back(&r);
        }
    }
    for (Rental *r : pastRentalForeachOwner) {
        cout << r->rentalId << endl;
    }
    return pastRentalForeachOwner;
}

void UserInterface::leaveCommentAndRatingForRenter(vector<Rental*> &rentalHistory) {
    int userChoice = displayReviewAndRatingRenterOptions();

    switch(userChoice) {
        case 0:
            return;
        default:
            if (userChoice > rentalHistory.size() || userChoice < 0) {
                cout << "Invalid choice!\n";
                return;
            }
            if (rentalHistory[userChoice - 1]->ownerRated) {   // if the owner has rated -> turn back
                cout << "You have rated for this renter!\nBringing you back...\n\n";
                return;
            }
            string comment, rating;
            cout << "----- Comment and Rating of User " << rentalHistory[userChoice - 1]->renter->username << endl;
            cout << "Your review on this renter: ";
            getline(cin >> ws, comment);
            cout << "Rate the renter: ";
            getline(cin, rating);
            rentalHistory[userChoice - 1]->ownerRated = true;  // owner has rated for the renter
            string reviewId;
            if (memberReviews.size() == 0) {
                reviewId = FileController::generateUniqueId("", "MBRV", 4);
            } else {
                reviewId = FileController::generateUniqueId(memberReviews.back().reviewId, "MBRV", 4);
            }
            string motorId = rentalHistory[userChoice - 1]->motorId;
            string renterId = rentalHistory[userChoice - 1]->renterId;
            memberReviews.push_back(MemberReview(reviewId, motorId, renterId, stod(rating), comment));
            updateRenterRating(renterId);
            cout << "Thank you for your review\n";
            return;
    }
}

void UserInterface::viewRentingHistory(Member *owner) {
    vector<Rental*> rentalHistory = findRentingHistory(owner);

    for (Rental *r : rentalHistory) {
        for (Member rt : members) {
            if (r->renterId == rt.userId){
                *r->renter = rt;
            }
        }
        for (Motorbike m : motorbikes) {
            if (r->motorId == m.motorId){
                *r->motorbike = m;
            }
        }
    }
    if (rentalHistory.size() == 0) {
        cout << "No renting history\n";
        return;
    } 
    for (int i = 0; i < rentalHistory.size(); i++) {
        cout << i + 1 << ". ";
        rentalHistory[i]->showInfoDetail();
    }
    leaveCommentAndRatingForRenter(rentalHistory);
}

// function to show choice to leave comment or exit
int UserInterface::displayReviewAndRatingRenterOptions() {
    int userChoice;
    cout << "Please choose your next move: \n";
    cout << "0. Exit\n1. Review and Rate your User\n";
    cout << "Enter your choice: ";
    cin >> userChoice;
    switch (userChoice) {
        case 0:
            return userChoice;
        case 1:
            cout << "Please choose the user that you want to review: ";
            cin >> userChoice; // return the renter that user want to review
            return userChoice;
            break;
        default:
            cout << "Invalid choice!\n";
            return 0;
            break;            
    } 
}

// function to update renter rating
void UserInterface::updateRenterRating(string renterId) {
    vector<MemberReview> ratingForRenter;
    double sum = 0;
    for (MemberReview mr : memberReviews) {
        if (mr.renterId == renterId) {
            ratingForRenter.push_back(mr);
        }
    }
    
    for (MemberReview mr : ratingForRenter) {
        if (mr.renterId == renterId) {
            sum += mr.rating;
        }
    }
    double finalRating = sum / ratingForRenter.size();
    for (Member &m : members) {
        if (m.userId == renterId) {
            m.renterRating = finalRating;
        }
    }
}

// function to return motobike base on the rental status "accepted"
void UserInterface::returnMotorbike(Member *renter) {
    if (renter->isRenting == 0) {
        cout << "Nothing to return\n";
        return;
    } else {
        string motorId; double totalPayingPoints;
        for (Rental &r : rentals) {
            if (renter->userId == r.renterId && r.status == "accepted") {
                r.status = "completed";
                motorId = r.motorId;
                totalPayingPoints = r.getTotalConsumingPoints();
            }
        }
        for (Motorbike &m : motorbikes) {
            if (motorId == m.motorId) {
                m.isAvailable = 1;
                // find the owner
                Member *owner = findMemberById(m.ownerId);
                // add credit points for the owner after turning back
                owner->addCreditPoints(totalPayingPoints);
            }
        }
        renter->isRenting = 0;
        cout << "Successfully return your motorbike\n";
    }
}

// display reviews of the motorbike from renters
void UserInterface::displayMotorbikeReviews(string motorId){
    int countRv = 1;
    cout << "------ Reviews of your motorbike ------\n";
    for (MotorbikeReview &motorRv : motorbikeReviews){
        if (motorRv.motorId == motorId){
            cout << countRv << ". ";
            motorRv.showInfo();
            countRv++;
        }
    }
    if (countRv == 1){
        cout << "There's no motorbike reviews!\n";
    }
}

// display reviews of the member as a renter
void UserInterface::displayMemberReviews(string memberId){
    int countRv = 1;
    cout << "------ Your ratings from motorbikes' owners ------\n";
    for (MemberReview &memRv : memberReviews){
        if (memRv.renterId == memberId){
            cout << countRv << ". ";
            memRv.showInfo();
            countRv++;
        }
    }
    if (countRv == 1){
        cout << "There's no reviews for you!\n";
    }
}

// display options for view the reviews
void UserInterface::viewReviewOptions(Member *member){
    int countReview = 0;
    if (member->motorbike == nullptr){  // if member doesn't have a motorbike
        displayMemberReviews(member->userId);
    } else {
        int choice;
        cout << "This is your menu:\n";
        cout << "0. Exit\n1. View reviews of your motorbike\n2. View your ratings from motorbikes' owners\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice){
            case 0:
                break;
            case 1:
                displayMotorbikeReviews(member->motorbike->motorId);
                break;
            case 2:
                displayMemberReviews(member->userId);
                break;
            default:
                break;
        }
    }
}

// main function for running UserInterface
void UserInterface::runInterface(){
    int userType = 1;
    bool isLoggedIn = false;
    Member *loggedInMem = nullptr;

    // login before creating Member object
    switch (userType) {
        case 0:
            cout << "Exiting Member interface...\n";
            break;
        case 1:
            do {
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
    while (isLoggedIn) {
        // load member's motorbike by searching from vector motorbikes
        loggedInMem->findMyMotorbike(motorbikes);
        bool hasMotorbike = (loggedInMem->motorbike != nullptr);

        if (hasMotorbike)
        { // if member has a motorbike
            userType = displayMemberMenu();
        }
        else // if the member has no motorbike, display differently
            userType = displayMemMenuNoMotorbike();

        switch (userType) {
            case 0:
                isLoggedIn = false;
                cout << "Logging you out...\n";
                break;
            case 1: // view personal info
                loggedInMem->showInfoDetail();
                break;
            case 2: // view motorbike info
                if (hasMotorbike) {
                    loggedInMem->motorbike->showInfoDetail();
                } else {
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
            case 7: // view history of rentals
                viewRentalHistory(loggedInMem);
                break;
            case 8: // view motorbike's rental history for owner
                viewRentingHistory(loggedInMem);
                break;
            case 9: // return motor
                returnMotorbike(loggedInMem);
                break;
            case 10: // view reviews
                viewReviewOptions(loggedInMem);
                break;
            default:
                cout << "Invalid choice. Please try again!\n";
                break;
        }
    }
    saveToFiles(); // saving all data to files
}