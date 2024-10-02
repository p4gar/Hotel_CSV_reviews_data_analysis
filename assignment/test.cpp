#include "csv_handler.hpp"

int main()
{
    // Initialize the handler with the positive and negative words files
    csvHandler handler("positive-words.txt", "negative-words.txt");

    // Open the CSV file containing reviews
    ifstream file("tripadvisor_hotel_reviews.csv");
    if (!file.is_open())
    {
        cerr << "Error opening CSV file!" << endl;
        return 1;
    }

    // Measure the time taken for processing the file
    auto start = chrono::high_resolution_clock::now();

    string line;
    while (getline(file, line))
    {
        // Split the line into review and rating using a comma as delimiter
        size_t commaPos = line.find_last_of(','); // Find the last comma before the rating
        if (commaPos == string::npos)
        {
            cerr << "Invalid format in line: " << line << endl;
            continue; // Skip malformed lines
        }

        string review = line.substr(0, commaPos);  // Extract review part
        string rating = line.substr(commaPos + 1); // Extract rating part (not used for now)

        cout << "Review: " << review << endl;
        cout << "Rating: " << rating << endl;
        cout << endl;

        // Count positive and negative words in the review
        handler.countSentimentWords(review);

        // Split review into individual words and update word frequency
        istringstream ss(review);
        string word;
        while (ss >> word) // Extract each word from the review
        {
            string cleanedWord;

            // Remove non-alphabetic characters and convert to lowercase
            for (char c : word)
            {
                if (isalpha(c)) // Only include alphabetic characters
                {
                    cleanedWord += tolower(c); // Convert to lowercase
                }
            }

            // Skip empty words
            if (cleanedWord.empty())
                continue;

            // Update frequency count for the cleaned word
            handler.updateWordFrequency(cleanedWord);
        }

        cout << "------------------------------------------" << endl;
        cout << endl;
        
    }

    file.close();

    // Measure and display the time taken
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "The total time taken for the sentiment analysis process using linear search is " << duration.count() << " microseconds" << endl;

    auto start2 = chrono::high_resolution_clock::now();
    handler.printWordStats();
    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);
    cout << "The total time taken for the report analysis using bubble sort is " << duration2.count() << " microseconds" << endl;

    system("pause");

    return 0;
}
