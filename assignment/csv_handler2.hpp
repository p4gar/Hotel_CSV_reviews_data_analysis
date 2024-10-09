#ifndef CSV_HANDLER2_HPP
#define CSV_HANDLER2_HPP

#include <iostream>
#include <fstream>
#include <cstring> // For strcmp and strtok
#include <cctype>  // For ispunct, tolower
#include <chrono>  // Include the chrono library for time measurement
#include <iomanip>
using namespace std;

class csvHandler
{
private:
    string positiveWords[3000];     // Store positive words
    string negativeWords[5000];     // Store negative words
    int positiveCount;              // Number of positive words loaded
    int negativeCount;              // Number of negative words loaded
    string uniqueWords[50000];      // To store unique words
    int wordFrequency[50000] = {0}; // To store frequencies of words
    int totalUniqueWords = 0;       // Track unique words count

    int totalReviews = 0;
    int totalPositiveWords = 0;
    int totalNegativeWords = 0;

public:
    csvHandler();

    int loadWords(const string &filename, string wordArray[], int maxSize);

    bool linearSearch(const string &word, const string wordArray[], int wordCount);

    bool binarySearch(const string &word, const string wordArray[], int wordCount);

    string cleanSentence(const string &word);

    double calcSentiScore(int posCount, int negCount);

    double countSentimentWordsusingLinearSearch(const string &review);

    double countSentimentWordsUsingBinarySearch(const string &review);

    void addWordFrequency(const string &word);

    void updateWordFrequency(const string &word);

    void printWordStats(bool useBubbleSort);

    void searchRecordByIndexLS(const string &filename, int index, csvHandler &csvHandlerObj);
    
    void searchRecordByIndexBS(const string &filename, int index, csvHandler &csvHandlerObj);

};

#endif