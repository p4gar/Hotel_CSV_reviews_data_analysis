#include "csv_handler.hpp"
using namespace std;

class csvHandler
{
private:
    string positiveWords[5000]; // Store positive words
    string negativeWords[3000]; // Store negative words
    int positiveCount;          // Number of positive words loaded
    int negativeCount;          // Number of negative words loaded
public:
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
    csvHandler(const string &positiveWordFile, const string &negativeWordFile)
    {
        positiveCount = loadWords(positiveWordFile, positiveWords, 1000);
        negativeCount = loadWords(negativeWordFile, negativeWords, 1000);
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
    void countSentimentWords(const string &review)
    {
        int positiveWordCount = 0;
        int negativeWordCount = 0;

        // Tokenize the review string
        stringstream ss(review);
        string word;

        cout << "Debugging cleaned words:\n";

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
        int revisedRating = (int)sentiScore;
        cout << "Sentiment score (1 - 5): " << sentiScore << " , thus the rating should be equal to " << revisedRating << endl;
    }
};

int main()
{
    csvHandler handler("positive-words.txt", "negative-words.txt");

    // Open the CSV file containing reviews
    ifstream file("tripadvisor_hotel_reviews.csv");
    if (!file.is_open())
    {
        cerr << "Error opening CSV file!" << endl;
        return 1;
    }

    auto start = chrono::high_resolution_clock::now();
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
        handler.countSentimentWords(review);
        cout << "------------------------------------------" << endl;
        cout << endl;
    }

    file.close();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "The total time taken for the sentiment analysis process using linear search is " << duration.count() << " microseconds" << endl;

    return 0;
}
