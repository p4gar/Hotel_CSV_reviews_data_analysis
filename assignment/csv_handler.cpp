#include "csv_handler.hpp"

// Constructor to initialize the handler with word files
csvHandler::csvHandler(const string &positiveWordFile, const string &negativeWordFile)
    : totalReviews(0), totalPositiveWords(0), totalNegativeWords(0) // Member initializer list
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
    int minRawScore = -totalWordCount;
    int maxRawScore = totalWordCount;

    double normalizedScore = (rawSentiScore - minRawScore) / (double)(maxRawScore - minRawScore);

    double finalSentiScore = 1 + (4 * normalizedScore);

    return finalSentiScore;
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
            totalPositiveWords++;
        }
        else if (wordExists(cleanedWord, negativeWords))
        {
            negativeWordCount++;
            totalNegativeWords++;
        }
    }

    cout << "Positive words: " << positiveWordCount << endl;
    cout << "Negative words: " << negativeWordCount << endl;

    double sentiScore = calcSentiScore(positiveWordCount, negativeWordCount);
    int revisedRating = static_cast<int>(sentiScore);
    cout << "Sentiment score (1 - 5): " << sentiScore << ", thus the rating should be equal to " << revisedRating << endl;
    totalReviews++;
}

// Function to update word frequency based on positive and negative words
void csvHandler::updateWordFrequency(const string &word)
{
    // Check if the word is in the positive words
    if (wordExists(word, positiveWords))
    {
        // Increment the frequency for positive words
        for (int i = 0; i < totalUniqueWords; i++)
        {
            if (uniqueWords[i] == word)
            {
                wordFrequency[i]++;
                return; // Exit after updating frequency
            }
        }

        // If the word is not found in uniqueWords, add it
        uniqueWords[totalUniqueWords] = word;
        wordFrequency[totalUniqueWords] = 1;
        totalUniqueWords++;
    }
    // Check if the word is in the negative words
    else if (wordExists(word, negativeWords))
    {
        // Increment the frequency for negative words
        for (int i = 0; i < totalUniqueWords; i++)
        {
            if (uniqueWords[i] == word)
            {
                wordFrequency[i]++;
                return; // Exit after updating frequency
            }
        }

        // If the word is not found in uniqueWords, add it
        uniqueWords[totalUniqueWords] = word;
        wordFrequency[totalUniqueWords] = 1;
        totalUniqueWords++;
    }
}

// Function to print word frequencies and max/min used words
void csvHandler::printWordStats()
{
    cout << "Total Reviews = " << totalReviews << endl;
    cout << "Total Counts of positive words = " << totalPositiveWords << endl;
    cout << "Total Counts of negative words = " << totalNegativeWords << endl;
    cout << endl
         << "Frequency of each word used in overall reviews, listed in ascending order based on frequency:" << endl;

    // Bubble Sort by frequency (ascending order)
    for (int i = 0; i < totalUniqueWords - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < totalUniqueWords - 1 - i; j++)
        {
            if (wordFrequency[j] > wordFrequency[j + 1])
            {
                // Swap frequencies
                int tempFreq = wordFrequency[j];
                wordFrequency[j] = wordFrequency[j + 1];
                wordFrequency[j + 1] = tempFreq;

                // Swap corresponding words
                string tempWord = uniqueWords[j];
                uniqueWords[j] = uniqueWords[j + 1];
                uniqueWords[j + 1] = tempWord;

                swapped = true;
            }
        }
        // If no elements were swapped, array is already sorted
        if (!swapped)
        {
            break;
        }
    }

    // Print sorted word frequencies
    for (int i = 0; i < totalUniqueWords; i++)
    {
        cout << uniqueWords[i] << " = " << wordFrequency[i] << " times" << endl;
    }

    // Determine max and min used words
    int maxFreq = wordFrequency[totalUniqueWords - 1];
    int minFreq = wordFrequency[0];

    cout << endl;
    cout << "Maximum used word(s) in the reviews: ";

    // Print words with maximum frequency
    bool first = true;
    for (int i = totalUniqueWords - 1; i >= 0 && wordFrequency[i] == maxFreq; i--)
    {
        if (!first)
        {
            cout << ", "; // Add a comma before the next word
        }
        cout << uniqueWords[i];
        first = false;
    }
    cout << endl;

    cout << "Minimum used word(s) in the reviews: ";

    // Print words with minimum frequency
    first = true;
    for (int i = 0; i < totalUniqueWords && wordFrequency[i] == minFreq; i++)
    {
        if (!first)
        {
            cout << ", "; // Add a comma before the next word
        }
        cout << uniqueWords[i];
        first = false;
    }
    cout << endl;
}
