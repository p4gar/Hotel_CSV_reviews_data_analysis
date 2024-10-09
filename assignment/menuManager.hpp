#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP

#include "csv_handler2.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring> // For strcmp and strtok
#include <cctype>  // For ispunct, tolower
#include <chrono>  // Include the chrono library for time measurement
#include <iomanip>
using namespace std;

class menuManager {
    
    public:
    string * reviews;
    string * ratings;
    int reviewCount;

    menuManager();

    void resetArrays();
    int binary_insert();
    int linear_bubble();
    void searchAndBinary(string * reviews, string * ratings, int reviewCount);
    void searchAndLinear(string * reviews, string * ratings, int reviewCount);
    void searchReview();

};

#endif