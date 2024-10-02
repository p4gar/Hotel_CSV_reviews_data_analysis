#include "csv_handler2.hpp"
using namespace std;

const int MAX_WORDS = 50000;

int main()
{
    // New Handler Object
    csvHandler handler1;
    int positiveWordCount, negativeWordCount;

    // Arrays to store word frequencies
    string wordArray[MAX_WORDS];
    int frequencyArray[MAX_WORDS] = {0};
    int wordArraySize = 0;

    // Variables to store total positive and negative words and total reviews
    int totalPositiveWords = 0;
    int totalNegativeWords = 0;
    int totalReviews = 0;

    // Load review CSV file
    ifstream file("tripadvisor_hotel_reviews.csv");
    if (!file.is_open())
    {
        cerr << "Error opening CSV file!" << endl;
        return 1;
    }

    // Start timer
    auto start = chrono::system_clock::now();

    // Count sentiment words in each review
    string line;
    while (getline(file, line))
    {
        // Separate lines into written review and numbered rating, using a comma as delimiter
        size_t commaPos = line.find_last_of(',');
        if (commaPos == string::npos)
        {
            cerr << "Invalid format in line: " << line << endl;
            continue; // Skip malformed lines
        }
        string review = line.substr(0, commaPos);
        string rating = line.substr(commaPos + 1);

        // Print review and rating
        cout << "Review: " << review << endl;
        cout << "Rating: " << rating << endl;
        cout << endl;

        // Count positive and negative words in the review
        handler1.countSentimentWordsUsingBinarySearch(review, positiveWordCount, negativeWordCount, wordArray, frequencyArray, wordArraySize);

        totalPositiveWords += positiveWordCount;
        totalNegativeWords += negativeWordCount;
        totalReviews++;

        cout << "Positive Words: " << positiveWordCount << endl;
        cout << "Negative Words: " << negativeWordCount << endl;

        double sentiScore = handler1.calcSentiScore(positiveWordCount, negativeWordCount);
        int revisedRating = (int)sentiScore;
        cout << "Sentiment Score (1 - 5): " << sentiScore << " , thus the rating should be equal to " << revisedRating << endl;

        cout << "-----------------------------------------" << endl;
        cout << endl;
    }

    // End timer
    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    // Close file
    file.close();

    // Print execution time
    cout << "The total time taken for the sentiment analysis process using binary search is " << duration.count() << " microseconds." << endl;

    system("pause");

    // Print total counts
    cout << "Total Reviews: " << totalReviews << endl;
    cout << "Total Counts of Positive Words: " << totalPositiveWords << endl;
    cout << "Total Counts of Negative Words: " << totalNegativeWords << endl;
    cout << endl;

    // Start timer
    auto start2 = chrono::system_clock::now();

    // Sort word frequencies
    handler1.customSort(wordArray, frequencyArray, wordArraySize);

    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);

    // Print tword frequencies in ascending order
    cout << "Frequency of each word used in overall reviews, listed in ascending order based on frequency: " << endl;
    for (int i = 0; i < wordArraySize; i++)
    {
        cout << wordArray[i] << ": " << frequencyArray[i] << " times" << endl;
    }
    cout << endl;

    // Print words with maximum frequency
    cout << "Minimum used word(s) in the reviews: ";

    bool first = true;
    int maxFreq = frequencyArray[handler1.findMaxIndex(frequencyArray, wordArraySize)]; // Find the maximum frequency

    for (int i = 0; i < wordArraySize; i++)
    {
        if (frequencyArray[i] == maxFreq)
        {
            if (!first)
            {
                cout << ", "; // Add a comma before the next word if it's not the first word
            }
            cout << wordArray[i];
            first = false;
        }
    }
    cout << endl;

    // Print words with minimum frequency
    cout << "Minimum used word(s) in the reviews: ";

    first = true;
    int minFreq = frequencyArray[handler1.findMinIndex(frequencyArray, wordArraySize)]; // Find the minimum frequency

    for (int i = 0; i < wordArraySize; i++)
    {
        if (frequencyArray[i] == minFreq)
        {
            if (!first)
            {
                cout << ", "; // Add a comma before the next word if it's not the first word
            }
            cout << wordArray[i];
            first = false;
        }
    }
    cout << endl;

    // Print execution time
    cout << "The total time taken for the report analysis process using insertion sort is " << duration2.count() << " microseconds." << endl;

    system("pause");

    return 0;
}