#ifndef CSV_HANDLER.HPP 
#define CSV_HANDLER.HPP 

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>   // For strcmp and strtok
#include <algorithm> // For remove_if to handle punctuation
#include <cctype>    // For ispunct, tolower
#include <chrono> // Include the chrono library for time measurement
using namespace std;

int loadWords(const string &filename, string wordArray[], int maxSize);

bool wordExists(const string &word, const string wordArray[], int wordCount);

string cleanWord(const string &word);

double calcSentiScore(int posCount, int negCount);

void countSentimentWords(const string &review, const string positiveWords[], int positiveCount, const string negativeWords[], int negativeCount);

#endif