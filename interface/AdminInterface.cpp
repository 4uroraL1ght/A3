#include <iostream>
#include <string>
#include <vector>
#include "../components/Motorbike.h"
#include "../action/FileController.h"
#include "AdminInterface.h"

#define MOTOR_FILE "data/Motorbike.txt"
#define MEMBER_FILE "data/Member.txt"

using namespace std;

AdminInterface::AdminInterface(){
    this->motorbikes = FileController::loadObjects(MOTOR_FILE, Motorbike::createObject);
    this->members = FileController::loadObjects(MEMBER_FILE, Member::createObject);
}

// safe all data (vectors of objects) back into files
void AdminInterface::saveToFiles(){
    FileController::writeObjects(MOTOR_FILE, motorbikes);
}
