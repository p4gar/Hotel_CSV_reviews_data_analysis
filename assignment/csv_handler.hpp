#ifndef CSV_HANDLER_HPP
#define CSV_HANDLER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>   // For strcmp and strtok
#include <algorithm> // For remove_if to handle punctuation
#include <cctype>    // For ispunct, tolower
#include <chrono>    // Include the chrono library for time measurement
using namespace std;

class csvHandler {
private:
    string positiveWords[5000]; // Store positive words
    string negativeWords[5000]; // Store negative words

public:
    // Constructor to initialize the handler with word files
    csvHandler(const string &positiveWordFile, const string &negativeWordFile);

    // Function to load words from a file into a vector
    void loadWords(const string &filename, string wordArray[]);

    // Function to check if a word exists in a vector
    bool wordExists(const string &word, const string wordArray[]);

    // Function to clean a word by removing punctuation and converting to lowercase
    string cleanWord(const string &word);

    // Function to calculate the sentiment score
    double calcSentiScore(int posCount, int negCount);

    // Function to count positive and negative words in a review
    void countSentimentWords(const string &review);
};

#endif
