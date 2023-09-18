#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../components/Motorbike.h"
#include "Rental.h"

using namespace std;

class Rental;       // forward declaration
class Motorbike;
class Member;

class FileController{
    private:
        /* data */
    public:
        // FileController();
        // ~FileController();

        // read from any file and return a vector of corresponding objects
        template <typename T>
        static vector<T> loadObjects(string fileName, T (*createObject)(string)){
            // takes in the file name and the function createObject() (which is created in every class)
            vector<T> objects;
            ifstream file(fileName);
            string line;
            if (!file.is_open()){
                cerr << "Problem with the file.\n";
            } 
            else {
                while (getline(file, line)){
                    T temp = createObject(line);
                    objects.push_back(move(temp));  // move object to new location
                }
            }
            file.close();
            return objects;
        }

        // take in file name and corresponding vector of objects -> write into file for saving
        template<typename T>
        static void writeObjects(string fileName, vector<T> objects) {
            ofstream file(fileName);
            if (!file.is_open()){
                cerr << "Problem with the file.\n";
            }
            else {
                for (T object : objects) {
                    file << object.formatForSaving();
                }
            }
            file.close();
        }

};
#endif