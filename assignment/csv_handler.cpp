#include "csv_handler.hpp"

// Constructor to initialize the handler with word files
csvHandler::csvHandler(const string &positiveWordFile, const string &negativeWordFile)
{
    // Load words into positive and negative arrays
    loadWords(positiveWordFile, positiveWords);
    loadWords(negativeWordFile, negativeWords);
}

// Function to load words from a file into an array
void csvHandler::loadWords(const string &filename, string wordArray[])
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string word;
    int i = 0; // Index for array
    while (file >> word)
    {
        if (i >= 5000)
        {
            cerr << "Exceeded maximum word limit for array" << endl;
            break;
        }
        wordArray[i++] = word; // Add word to array
    }

    file.close();
}

// Function to check if a word exists in an array
bool csvHandler::wordExists(const string &word, const string wordArray[])
{
    for (int i = 0; i < 5000; i++)
    {
        if (wordArray[i] == word)
        {
            return true;
        }
    }
    return false;
}

// Function to clean a word by removing punctuation and converting to lowercase
string csvHandler::cleanWord(const string &word)
{
    string cleanedWord;
    for (char ch : word)
    {
        if (!ispunct(ch))
        {
            cleanedWord += tolower(ch); // Convert to lowercase and remove punctuation
        }
    }
    return cleanedWord;
}

// Function to calculate the sentiment score
double csvHandler::calcSentiScore(int posCount, int negCount)
{
    int rawSentiScore = posCount - negCount;
    int totalWordCount = posCount + negCount;
    double normalizedScore = (rawSentiScore - -totalWordCount) / (double)(totalWordCount);
    return 1 + (4 * normalizedScore); // Scale between 1 and 5
}

// Function to count positive and negative words in a review
void csvHandler::countSentimentWords(const string &review)
{
    int positiveWordCount = 0;
    int negativeWordCount = 0;

    stringstream ss(review);
    string word;

    while (ss >> word)
    {
        string cleanedWord = cleanWord(word);
        if (wordExists(cleanedWord, positiveWords))
        {
            positiveWordCount++;
        }
        else if (wordExists(cleanedWord, negativeWords))
        {
            negativeWordCount++;
        }
    }

    cout << "Positive words: " << positiveWordCount << endl;
    cout << "Negative words: " << negativeWordCount << endl;

    double sentiScore = calcSentiScore(positiveWordCount, negativeWordCount);
    int revisedRating = static_cast<int>(sentiScore);
    cout << "Sentiment score (1 - 5): " << sentiScore << ", thus the rating should be equal to " << revisedRating << endl;
}
