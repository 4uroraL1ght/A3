#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
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

        // generate new object's id following the pattern of the class and previous object's id
        /* lastId - id of the previous object in the vector
            preifx - the "string" part of the id
            startIndex - the starting position of the numeric part of id */
        static string generateUniqueId(string lastId, string prefix, int startIndex) {
            if (lastId == "") {
                return prefix + string(3 - 1, '0') + "1";  // Return the first ID if the vector is empty
            }

            string numericPart = lastId.substr(startIndex);
            int nextNumericValue = stoi(numericPart);
            nextNumericValue++;
            stringstream ss;
            ss << setw(3) << setfill('0') << nextNumericValue;
            return prefix + ss.str();
        }

};
#endif