#include "csv_handler.hpp"
using namespace std;

// Function to load words from a file into an array
int loadWords(const string &filename, string wordArray[], int maxSize)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return 0;
    }

    string word;
    int count = 0;
    while (file >> word && count < maxSize)
    {
        wordArray[count] = word;
        count++;
    }

    file.close();
    return count; // Return the number of words loaded
}

// Function to check if a word exists in an array
bool wordExists(const string &word, const string wordArray[], int wordCount)
{
    for (int i = 0; i < wordCount; i++)
    {
        if (word == wordArray[i])
        {
            return true;
        }
    }
    return false;
}

// Function to clean a word by removing punctuation and converting to lowercase
string cleanWord(const string &word)
{
    string cleanedWord;
    for (char ch : word)
    {
        if (!ispunct(ch))
        {                               // Remove punctuation
            cleanedWord += tolower(ch); // Convert to lowercase
        }
    }
    return cleanedWord;
}

double calcSentiScore(int posCount, int negCount)
{
    // Step 1: Calculate the Raw Sentiment Score
    int rawSentiScore = posCount - negCount;

    // Step 2: Calculate total word count and derive Min and Max Raw Scores
    int totalWordCount = posCount + negCount;
    int minRawScore = -totalWordCount;
    int maxRawScore = totalWordCount;

    // Step 3: Calculate Normalized Score
    double normalizedScore = (rawSentiScore - minRawScore) / (double)(maxRawScore - minRawScore);

    // Step 4: Calculate final Sentiment Score (between 1 and 5)
    double finalSentiScore = 1 + (4 * normalizedScore);

    return finalSentiScore;
}

// Function to count positive and negative words in a review
void countSentimentWords(const string &review, const string positiveWords[], int positiveCount, const string negativeWords[], int negativeCount)
{
    int positiveWordCount = 0;
    int negativeWordCount = 0;
    int revisedRating; // rounded up rating

    // Tokenize the review string
    stringstream ss(review);
    string word;

    cout << "Debugging cleaned words:\n"; // Debugging output for cleaned words
    while (ss >> word)
    {
        // Clean the word
        string cleanedWord = cleanWord(word);

        // Print cleaned word for debugging
        cout << cleanedWord << " ";

        // Check for the word in positive and negative arrays
        if (wordExists(cleanedWord, positiveWords, positiveCount))
        {
            positiveWordCount++;
        }
        else if (wordExists(cleanedWord, negativeWords, negativeCount))
        {
            negativeWordCount++;
        }
    }
    cout << endl;
    cout << endl;

    // Print results
    cout << "Positive words: " << positiveWordCount << endl;
    cout << "Negative words: " << negativeWordCount << endl;

    double sentiScore = calcSentiScore(positiveWordCount, negativeWordCount);
    revisedRating = (int)sentiScore;
    cout << "Sentiment score (1 - 5): " << sentiScore << " , thus the rating should be equal to " << revisedRating << endl;
}

int main()
{
    // Load positive and negative words from files
    const int MAX_WORDS = 5000;
    string positiveWords[MAX_WORDS];
    string negativeWords[MAX_WORDS];

    int positiveCount = loadWords("positive-words.txt", positiveWords, MAX_WORDS);
    int negativeCount = loadWords("negative-words.txt", negativeWords, MAX_WORDS);

    // Open the CSV file containing reviews
    ifstream file("tripadvisor_hotel_reviews.csv");
    if (!file.is_open())
    {
        cerr << "Error opening CSV file!" << endl;
        return 1;
    }

    string line;
    while (getline(file, line))
    {
        // Split the line into review and rating using a comma as delimiter
        size_t commaPos = line.find_last_of(',');  // Find the last comma before the rating
        string review = line.substr(0, commaPos);  // Extract review part
        string rating = line.substr(commaPos + 1); // Extract rating part (not used for now)

        cout << "Review: " << review << endl;
        cout << "Rating: " << rating << endl;
        cout << endl;

        // Count positive and negative words in the review
        countSentimentWords(review, positiveWords, positiveCount, negativeWords, negativeCount);
        cout << "------------------------------------------" << endl;
        cout << endl;
    }

    file.close();
    return 0;
}
