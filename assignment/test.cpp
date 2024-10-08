#include "csv_handler2.hpp"

const int MAX_WORDS = 50000;

int main()
{
    // New Handler Object
    csvHandler handler1;

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
        handler1.countSentimentWordsusingLinearSearch(review);

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
            handler1.updateWordFrequency(cleanedWord);
        }

        cout << "-----------------------------------------" << endl;
        cout << endl;
    }

    // End timer
    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    // Close file
    file.close();

    // Print execution time
    cout << "The total time taken for the sentiment analysis process using linear search is " << duration.count() << " microseconds." << endl;

    system("pause");

    // Start timer
    auto start2 = chrono::system_clock::now();

    // Sort word frequencies
    handler1.printWordStats(true);

    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);

    // Print execution time
    cout << "The total time taken for the report analysis process using bubble sort is " << duration2.count() << " microseconds." << endl;

    system("pause");

    cout << "Would you like to search for a specific review? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        string filename = "tripadvisor_hotel_reviews.csv";

        // Ask the user for the index they want to search
        int recordIndex;
        cout << "Enter the index of the record you want to search for: ";
        cin >> recordIndex;
        cout << "-----------------------------------------" << endl;

        // Call the function to search for the record by index
        handler1.searchRecordByIndexLS(filename, recordIndex, handler1);

    }

    return 0;
}