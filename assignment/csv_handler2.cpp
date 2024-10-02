#include "csv_handler2.hpp"
using namespace std;

csvHandler::csvHandler()
{
    // Load positive and negative words into arrays
    positiveCount = loadWords("positive-words.txt", positiveWords, 3000);
    negativeCount = loadWords("negative-words.txt", negativeWords, 5000);

    // Sort the word arrays to ensure binary search works
    insertionSort(positiveWords, positiveCount);
    insertionSort(negativeWords, negativeCount);
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

void csvHandler::insertionSort(string wordArray[], int wordCount)
{
    for (int i = 1; i < wordCount; i++) 
    {
        string key = wordArray[i];
        int j = i - 1;

        while (j >= 0 && wordArray[j] > key)
        {
            wordArray[j + 1] = wordArray[j];
            j--;
        }
        wordArray[j + 1] = key;
    }
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

bool csvHandler::binarySearch(const string &word, const string wordArray[], int wordCount)
{
    int low = 0, high = wordCount - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (wordArray[mid] == word) {
            return true;
        } else if (wordArray[mid] < word) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
}

// Increase word frequency
void csvHandler::addWordFrequency(const string &word, string wordArray[], int frequencyArray[], int &size)
{
    // Check if the word is in the positive words
    if (binarySearch(word, positiveWords, positiveCount))
    {
        // Increment the frequency for positive words
        for (int i = 0; i < size; i++)
        {
            if (wordArray[i] == word)
            {
                frequencyArray[i]++;
                return; // Exit after updating frequency
            }
        }

        wordArray[size] = word;
        frequencyArray[size] = 1;
        size++;
    }
    // Check if the word is in the negative words
    else if (binarySearch(word, negativeWords, negativeCount))
    {
        // Increment the frequency for negative words
        for (int i = 0; i < size; i++)
        {
            if (wordArray[i] == word)
            {
                frequencyArray[i]++;
                return; // Exit after updating frequency
            }
        }

        // If the word is not found in uniqueWords, add it
        wordArray[size] = word;
        frequencyArray[size] = 1;
        size++;
    }
}

void csvHandler::countSentimentWordsUsingBinarySearch(const string &review, int &positiveWordCount, int &negativeWordCount, string wordArray[], int frequencyArray[], int &wordArraySize)  // diff
{
    positiveWordCount = 0;
    negativeWordCount = 0;

    stringstream ss(review);
    string word;

    cout << "Debugging cleaned words:\n";

    while (ss >> word)
    {
        string cleanedWord = cleanSentence(word);

        if (binarySearch(cleanedWord, positiveWords, positiveCount))
        {
            positiveWordCount++;
            addWordFrequency(cleanedWord, wordArray, frequencyArray, wordArraySize);
        }
        else if (binarySearch(cleanedWord, negativeWords, negativeCount))
        {
            negativeWordCount++;
            addWordFrequency(cleanedWord, wordArray, frequencyArray, wordArraySize);
        }
    }

    cout << endl;
    cout << endl;
}

// Sort arrays using insertion sort
void csvHandler::customSort(string wordArray[], int frequencyArray[], int size)
{
    for (int i = 1; i < size; i++)
    {
        string keyWord = wordArray[i];
        int keyFrequency = frequencyArray[i];
        int j = i - 1;

        while (j >= 0 && frequencyArray[j] > keyFrequency)
        {
            wordArray[j + 1] = wordArray[j];
            frequencyArray[j + 1] = frequencyArray[j];
            j--;
        }
        wordArray[j + 1] = keyWord;
        frequencyArray[j + 1] = keyFrequency;
    }
}

// Find index of maximum element
int csvHandler::findMaxIndex(int frequencyArray[], int size)
{
    int maxIndex = 0;
    for (int i = 1; i < size; i++)
    {
        if (frequencyArray[i] > frequencyArray[maxIndex])
        {
            maxIndex = i;
        }
    }
    return maxIndex;
}

// Find index of minimum element
int csvHandler::findMinIndex(int frequencyArray[], int size)
{
    int minIndex = 0;
    for (int i = 1; i < size; i++)
    {
        if (frequencyArray[i] < frequencyArray[minIndex])
        {
            minIndex = i;
        }
    }
    return minIndex;
}