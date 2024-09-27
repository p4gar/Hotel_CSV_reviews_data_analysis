#ifndef CSV_HANDLER2.HPP 
#define CSV_HANDLER2.HPP 

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>   // For strcmp and strtok
#include <algorithm> // For remove_if to handle punctuation
#include <cctype>    // For ispunct, tolower
#include <chrono> // Include the chrono library for time measurement
using namespace std;

class csvHandler
{
    private:
    string positiveWords[5000]; // Store positive words
    string negativeWords[3000]; // Store negative words
    int positiveCount;          // Number of positive words loaded
    int negativeCount;          // Number of negative words loaded

    public:
    csvHandler();
    
    void loadSentiWords(const string &positiveWords, const string &negativeWords);
    
    int loadWords(const string &filename, string wordArray[], int maxSize);

    void insertionSort(string wordArray[], int count);

    bool wordExists(const string &word, const string wordArray[], int wordCount);

    bool binarySearch(const string &word, const string wordArray[], int wordCount);

    string cleanSentence(const string &word);

    double calcSentiScore(int posCount, int negCount);

    void countSentimentWordsusingLinearSearch(const string &review);

    void countSentimentWordsUsingBinarySearch(const string &review, int &positiveWordCount, int &negativeWordCount);

};


#endif