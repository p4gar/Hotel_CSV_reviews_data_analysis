#ifndef ARRAYFROMCSV_H
#define ARRAYFROMCSV_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class ArrayFromCSV {
    public:
    ArrayFromCSV();
    
    string** readCSV(const string& fileName, int& numRows, int& numCols){
        ifstream file("")
    }

    void printArray(string** data, int numRows, int numCols);
};
#endif