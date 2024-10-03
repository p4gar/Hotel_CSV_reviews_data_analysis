#include "csv_handler2.hpp"
using namespace std;

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
        handler1.countSentimentWordsUsingBinarySearch(review);

        

        
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

    auto start2 = chrono::system_clock::now();

    // Sort word frequencies
    handler1.printWordStats(false);

    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);

    // Print execution time
    cout << "The total time taken for the report analysis process using insertion sort is " << duration2.count() << " microseconds." << endl;

    system("pause");

    return 0;
}