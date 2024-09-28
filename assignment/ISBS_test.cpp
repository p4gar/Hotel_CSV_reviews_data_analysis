#include "csv_handler2.hpp"
using namespace std;

int main()
{
    // New Handler Object
    csvHandler handler1;
    int positiveWordCount, negativeWordCount;

    // Map to store word frequencies
    map<string, int> wordFrequencyMap;

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
        string review = line.substr(0, commaPos);
        string rating = line.substr(commaPos + 1);

        // Print review and rating
        cout << "Review: " << review << endl;
        cout << "Rating: " << rating << endl;
        cout << endl;

        // Count positive and negative words in the review
        handler1.countSentimentWordsUsingBinarySearch(review, positiveWordCount, negativeWordCount,  wordFrequencyMap);
        
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

    system("pause");

    // Print total counts
    cout << "Total Reviews: " << totalReviews << endl;
    cout << "Total Counts of Positive Words: " << totalPositiveWords << endl;
    cout << "Total Counts of Negative Words: " << totalNegativeWords << endl;
    cout << endl;

    // Sort word frequencies
    vector<pair<string, int>> sortedWords(wordFrequencyMap.begin(), wordFrequencyMap.end());
    sort(sortedWords.begin(), sortedWords.end(), [](const pair<string, int>& a, const pair<string, int>& b) 
    {
        return a.second < b.second;
    });

    // Print tword frequencies in ascending order
    cout << "Frequency of each word used in overall reviews, listed in ascending order based on frequency: " << endl;
    for (const auto &pair : sortedWords)
    {
        cout << pair.first << ": " << pair.second << " times" << endl;
    }
    cout << endl;

    // Find words with maximum and minimum frequencies
    auto maxIt = max_element(sortedWords.begin(), sortedWords.end(), [](const pair<string, int>& a, const pair<string, int>& b) 
    {
        return a.second < b.second;
    });
    auto minIt = min_element(sortedWords.begin(), sortedWords.end(), [](const pair<string, int>& a, const pair<string, int>& b) 
    {
        return a.second < b.second;
    });
    
    // Print words with maximum and minimum frequencies
    cout << "Maximum used word in the reviews: " << maxIt->first << " = " << maxIt->second << " times" << endl;
    cout << "Minimum used word in the reviews: " << minIt->first << " = " << minIt->second << " times" << endl;
    cout << endl;
    
    // Print execution time
    cout << "The total time taken for the sentiment analysis process using binary search is " << duration.count() << " microseconds." << endl;

    return 0;
}