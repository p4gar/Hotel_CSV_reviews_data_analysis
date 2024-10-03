#include "csv_handler2.hpp"

csvHandler::csvHandler()
{
    // Load positive and negative words into arrays
    positiveCount = loadWords("positive-words.txt", positiveWords, 3000);
    negativeCount = loadWords("negative-words.txt", negativeWords, 5000);
}

// Function to load words from a file into an array
int csvHandler::loadWords(const string &filename, string wordArray[], int maxSize)
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
    return count;
}

string csvHandler::cleanSentence(const string &word)
{
    string cleanedWord;
    for (char ch : word)
    {
        if (!ispunct(ch))
        {
            cleanedWord += tolower(ch);
        }
    }
    return cleanedWord;
}

double csvHandler::calcSentiScore(int positiveCount, int negativeCount)
{
    int rawSentiScore = positiveCount - negativeCount;

    int totalWordCount = positiveCount + negativeCount;
    int minRawScore = -totalWordCount;
    int maxRawScore = totalWordCount;

    double normalizedScore = (rawSentiScore - minRawScore) / (double)(maxRawScore - minRawScore);

    double finalSentiScore = 1 + (4 * normalizedScore);

    return finalSentiScore;
}

// Function to check if a word exists in an array
bool csvHandler::linearSearch(const string &word, const string wordArray[], int wordCount)
{
    for (int i = 0; i < wordCount; i++)
    {
        if (wordArray[i] == word)
        {
            return true;
        }
    }
    return false;
}

bool csvHandler::binarySearch(const string &word, const string wordArray[], int wordCount)
{
    int low = 0, high = wordCount - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (wordArray[mid] == word)
        {
            return true;
        }
        else if (wordArray[mid] < word)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return false;
}

// Increase word frequency
void csvHandler::addWordFrequency(const string &word)
{
    // Check if the word is in the positive words
    if (binarySearch(word, positiveWords, positiveCount))
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

        uniqueWords[totalUniqueWords] = word;
        wordFrequency[totalUniqueWords] = 1;
        totalUniqueWords++;
    }
    // Check if the word is in the negative words
    else if (binarySearch(word, negativeWords, negativeCount))
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

// Function to update word frequency based on positive and negative words
void csvHandler::updateWordFrequency(const string &word)
{
    // Check if the word is in the positive words
    if (linearSearch(word, positiveWords, positiveCount))
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
    else if (linearSearch(word, negativeWords, negativeCount))
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

void csvHandler::countSentimentWordsusingLinearSearch(const string &review)
{
    int positiveWordCount = 0;
    int negativeWordCount = 0;

    stringstream ss(review);
    string word;

    while (ss >> word)
    {
        string cleanedWord = cleanSentence(word);
        if (linearSearch(cleanedWord, positiveWords, positiveCount))
        {
            positiveWordCount++;
            totalPositiveWords++;
        }
        else if (linearSearch(cleanedWord, negativeWords, positiveCount))
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

void csvHandler::countSentimentWordsUsingBinarySearch(const string &review) // diff
{
    int positiveWordCount = 0;
    int negativeWordCount = 0;

    stringstream ss(review);
    string word;

    cout << "Debugging cleaned words:\n";

    while (ss >> word)
    {
        string cleanedWord = cleanSentence(word);

        if (binarySearch(cleanedWord, positiveWords, positiveCount))
        {
            positiveWordCount++;
            addWordFrequency(cleanedWord);
        }
        else if (binarySearch(cleanedWord, negativeWords, negativeCount))
        {
            negativeWordCount++;
            addWordFrequency(cleanedWord);
        }
    }

    cout << "Positive words: " << positiveWordCount << endl;
    cout << "Negative words: " << negativeWordCount << endl;

    double sentiScore = calcSentiScore(positiveWordCount, negativeWordCount);
    int revisedRating = static_cast<int>(sentiScore);
    cout << "Sentiment score (1 - 5): " << sentiScore << ", thus the rating should be equal to " << revisedRating << endl;
    totalReviews++;
}

void csvHandler::printWordStats(bool useBubbleSort)
{
    cout << "Total Reviews = " << totalReviews << endl;
    cout << "Total Counts of positive words = " << totalPositiveWords << endl;
    cout << "Total Counts of negative words = " << totalNegativeWords << endl;
    cout << endl
         << "Frequency of each word used in overall reviews, listed in ascending order based on frequency:" << endl;

    if (useBubbleSort)
    {
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
    }
    else
    {
        // Insertion Sort by frequency (ascending order)
        for (int i = 1; i < totalUniqueWords; i++)
        {
            int keyFreq = wordFrequency[i];
            string keyWord = uniqueWords[i];
            int j = i - 1;

            while (j >= 0 && wordFrequency[j] > keyFreq)
            {
                wordFrequency[j + 1] = wordFrequency[j];
                uniqueWords[j + 1] = uniqueWords[j];
                j--;
            }
            wordFrequency[j + 1] = keyFreq;
            uniqueWords[j + 1] = keyWord;
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
