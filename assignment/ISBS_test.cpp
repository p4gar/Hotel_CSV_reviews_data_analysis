#include "csv_handler2.hpp"
using namespace std;

int main()
{
    // New Handler Object
    csvHandler handler1;
    int option = 0;

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
    cout << endl;

    auto start2 = chrono::system_clock::now();

    // Sort word frequencies
    handler1.printWordStats(false);

    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);

    // Print execution time
    cout << "The total time taken for the report analysis process using insertion sort is " << duration2.count() << " microseconds." << endl;

    system("pause");

    bool choice = true;
    string input;

    while (choice)
    {
        cout << endl;
        cout << "Would you like to search for a specific review? (y/n): ";
        cin >> input;

        if (input == "y" || input == "Y")
        {
            string filename = "tripadvisor_hotel_reviews.csv";
            int recordIndex;

            cout << "Enter the index of the record you want to analyze (1 - 20492): ";
            cin >> recordIndex;
            cout << string(54, '-') << endl;

            handler1.searchRecordByIndex(filename, recordIndex, handler1);

            system("pause");
        }
        else if (input == "n" || input == "N")
        {
            choice = false;
        }
        else
        {
            cout << "Invalid choice. Please enter 'y' or 'n'." << endl;
        }
    }

    return 0;
}