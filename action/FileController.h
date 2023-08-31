#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../components/Motorbike.h"

using namespace std;

class FileController{
    private:
        /* data */
    public:
        // FileController();
        // ~FileController();

        template <typename T>
        static vector<T> loadObjects(string fileName, T (*createObject)(string)){
            vector<T> objects;
            ifstream file(fileName);
            string line;
            if (!file.is_open()){
                cerr << "Problem with the file.\n";
            } 
            else {
                while (getline(file, line)){
                    T temp = createObject(line);
                    objects.push_back(temp);
                }
            }
            file.close();
            cout << "File closed.\n";
            return objects;
        }

};
#endif