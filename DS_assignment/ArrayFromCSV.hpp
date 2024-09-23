#ifndef ARRAYFROMCSV_HPP
#define ARRAYFROMCSV_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class ArrayFromCSV
{
public:

    int countColumns(const string &line)
    {
        stringstream ss(line);
        string cell;
        int colCount = 0;
        while (getline(ss, cell, ','))
        {
            colCount++;
        }
        return colCount;
    }

    string **readCSV(const string &fileName, int &numRows, int &numCols)
    {
        ifstream file(fileName);
        if (!file.is_open())
        {
            cerr << "Error opening file!" << endl;
            return nullptr;
        }

        string line;
        numRows = 0;
        numCols = 0;

        // First pass: Count the number of rows and columns
        while (getline(file, line))
        {
            if (numCols == 0)
            {
                numCols = countColumns(line); // Set the number of columns based on the first row
            }
            numRows++;
        }

        // Rewind the file to read data
        file.clear();
        file.seekg(0, ios::beg);

        // Dynamically allocate memory for the 2D array
        string **data = new string *[numRows];
        for (int i = 0; i < numRows; i++)
        {
            data[i] = new string[numCols];
        }

        // Read data from CSV into the 2D array
        int row = 0;
        while (getline(file, line) && row < numRows)
        {
            stringstream ss(line);
            string cell;
            int col = 0;
            while (getline(ss, cell, ',') && col < numCols)
            {
                data[row][col] = cell;
                col++;
            }
            row++;
        }

        // Close the file after reading
        file.close();

        return data;
    }

    void printArray(string **data, int numRows, int numCols)
    {
        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j < numCols && !data[i][j].empty(); j++)
            {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    void freeArray(string **data, int numRows)
    {
        for (int i = 0; i < numRows; i++)
        {
            delete[] data[i];
        }
        delete[] data;
    }
};

#endif