#include "csv_handler2.hpp"
using namespace std;

int main()
{
    // New Handler Object
    csvHandler handler1;
    int positiveWordCount, negativeWordCount;

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
        handler1.countSentimentWordsUsingBinarySearch(review, positiveWordCount, negativeWordCount);
        
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

    return 0;
}