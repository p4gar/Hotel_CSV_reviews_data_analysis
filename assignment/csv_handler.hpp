#ifndef CSV_HANDLER_HPP
#define CSV_HANDLER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring> // For strcmp and strtok
#include <cctype>  // For ispunct, tolower
#include <chrono>  // Include the chrono library for time measurement
using namespace std;

class csvHandler
{
private:
    string positiveWords[3000]; // Store positive words
    string negativeWords[5000]; // Store negative words
    string uniqueWords[50000];  // To store unique words
    int wordFrequency[50000] = {0}; // To store frequencies of words
    int totalUniqueWords = 0; // Track unique words count

    int totalReviews = 0;
    int totalPositiveWords = 0;
    int totalNegativeWords = 0;

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

    // Function to print word frequencies and max/min used words
    void printWordStats();

    // Function to add or update word frequency
    void updateWordFrequency(const string &word);
};

#endif
