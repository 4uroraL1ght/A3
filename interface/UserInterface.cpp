#include <iostream>
#include <string>
#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"
#include "UserInterface.h"

#define MOTOR_FILE "data/Motorbike.txt"
#define MEMBER_FILE "data/Member.txt"

using namespace std;

UserInterface::UserInterface(){
    motorbikes = FileController::loadObjects(MOTOR_FILE, Motorbike::createObject);
    this->members = FileController::loadObjects(MEMBER_FILE, Member::createObject);
}

// safe all data (vectors of objects) back into files
void UserInterface::saveToFiles(){
    FileController::writeObjects(MOTOR_FILE, motorbikes);
}

Motorbike* UserInterface::findMyMotorbike(string ownerId){
    for (auto& mt : motorbikes){
        if (ownerId == mt.ownerId){
            return &mt;
        }
    }
    return nullptr;
}

// main function for running UserInterface
void UserInterface::runInterface(){
    /* testing */
    // find and assign the motorbike of the member
    members[0].motorbike = findMyMotorbike(members[0].userId);
    
    // if the user has added their motorbike
    if (members[0].motorbike != nullptr){
        members[0].motorbike->showInfo();
    }
}