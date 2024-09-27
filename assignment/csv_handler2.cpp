#include "csv_handler2.hpp"
using namespace std;

csvHandler::csvHandler()
{
    // Load positive and negative words into arrays
    positiveCount = loadWords("positive-words.txt", positiveWords, 5000);
    negativeCount = loadWords("negative-words.txt", negativeWords, 3000);

    // Sort positive and negative words using insertion sort algorithm
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

void csvHandler::countSentimentWordsUsingBinarySearch(const string &review, int &positiveWordCount, int &negativeWordCount) // diff
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
        }
        else if (binarySearch(cleanedWord, negativeWords, negativeCount))
        {
            negativeWordCount++;
        }
    }

    cout << endl;
    cout << endl;
}
