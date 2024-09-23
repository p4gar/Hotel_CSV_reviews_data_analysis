#include "ArrayFromCSV.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{

    int numRows, numCols;

    // Read CSV file and store data in a 2D dynamically allocated array
    string **data = readCSV("tripadvisor_hotel_reviews.csv", numRows, numCols);

    // Check if data was successfully read
    if (data != nullptr)
    {
        // Print the data from the CSV file
        cout << "CSV Data: " << endl;
        printArray(data, numRows, numCols);

        // Free the dynamically allocated memory
        freeArray(data, numRows);
    }
    else
    {
        cerr << "Failed to read CSV file." << endl;
    }

    return 0;
}