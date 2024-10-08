#include "csv_handler2.hpp"
using namespace std;

// Binary Search & Insertion Sort Algorithm
int binary_insert()
{
    system("cls");
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

        cout << endl;
        cout << string(60, '*') << endl;
        cout << endl;
    }

    // End timer
    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    auto seconds = chrono::duration_cast<chrono::seconds>(end - start);

    // Close file
    file.close();

    // Print execution time
    cout << "The total time taken for the sentiment analysis process using binary search is " << duration.count() << " microseconds / " << seconds.count() << " seconds." << endl;

    cout << "Press 'Enter' to see overall review sentiment using insertion sort algorithm.";
    cin.ignore();
    cin.get();
    system("cls");

    auto start2 = chrono::system_clock::now();

    // Sort word frequencies
    handler1.printWordStats(false);

    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);
    auto seconds2 = chrono::duration_cast<chrono::seconds>(stop2 - start2);

    // Print execution time
    cout << "The total time taken for the report analysis process using insertion sort is " << duration2.count() << " microseconds / " << seconds2.count() << " seconds." << endl;

    cout << "Press 'Enter' twice to return to main menu.";
    cin.ignore();
    cin.get();
    system("cls");

    return 0;
}

// Linear Search & Bubble Sort Algorithm
int linear_bubble()
{
    system("cls");
    // New Handler Object
    csvHandler handler2;

    ifstream file("tripadvisor_hotel_reviews.csv");
    if (!file.is_open())
    {
        cerr << "Error opening CSV file!" << endl;
        return 0;
    }

    // Start timer
    auto start3 = chrono::system_clock::now();

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
        handler2.countSentimentWordsusingLinearSearch(review);

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
            handler2.updateWordFrequency(cleanedWord);
        }

        cout << endl;
        cout << string(60, '*') << endl;
        cout << endl;
    }

    // End timer
    auto end3 = chrono::system_clock::now();
    auto duration3 = chrono::duration_cast<chrono::microseconds>(end3 - start3);
    auto seconds3 = chrono::duration_cast<chrono::seconds>(end3 - start3);

    // Close file
    file.close();

    // Print execution time
    cout << "The total time taken for the sentiment analysis process using linear search is " << duration3.count() << " microseconds / " << seconds3.count() << " seconds." << endl;

    cout << "Press 'Enter' to see overall review sentiment using bubble sort algorithm.";
    cin.ignore();
    cin.get();
    system("cls");

    // Start timer
    auto start4 = chrono::system_clock::now();

    // Sort word frequencies
    handler2.printWordStats(true);

    auto stop4 = chrono::high_resolution_clock::now();
    auto duration4 = chrono::duration_cast<chrono::microseconds>(stop4 - start4);
    auto seconds4 = chrono::duration_cast<chrono::seconds>(stop4 - start4);

    // Print execution time
    cout << "The total time taken for the report analysis process using bubble sort is " << duration4.count() << " microseconds / " << seconds4.count() << " seconds." << endl;

    cout << "Press 'Enter' twice to return to main menu.";
    cin.ignore();
    cin.get();
    system("cls");

    return 0;
}

void searchAndBinary()
{
    csvHandler handler3;
    bool choice = true;
    string input;

    string filename = "tripadvisor_hotel_reviews.csv";
    int recordIndex;

    while (choice)
    {
        system("cls");
        cout << "Enter the index of the record you want to analyze (1 - 20492): ";

        if (cin >> recordIndex)
        {
            cout << endl;
            cout << string(60, '-') << endl;

            handler3.searchRecordByIndexLS(filename, recordIndex, handler3);

            cout << endl;
            cout << string(60, '-') << endl;
            cout << endl;

            cout << "Would you still like to search for a specific review? (Any key to continue, 'X' to return to menu): ";
            cin >> input;

            if (input == "x" || input == "X")
            {
                cout << endl;
                cout << string(60, '-') << endl;
                choice = false;
            }
        }
        else
        {
            cout << string(60, '-') << endl;
            cout << "Invalid input. Please enter a number." << endl;
            cout << string(60, '-') << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

void searchAndLinear()
{
    csvHandler handler3;
    bool choice = true;
    string input;

    string filename = "tripadvisor_hotel_reviews.csv";
    int recordIndex;

    while (choice)
    {
        system("cls");
        cout << "Enter the index of the record you want to analyze (1 - 20492): ";

        if (cin >> recordIndex)
        {
            cout << endl;
            cout << string(60, '-') << endl;

            handler3.searchRecordByIndexLS(filename, recordIndex, handler3);

            cout << endl;
            cout << string(60, '-') << endl;
            cout << endl;

            cout << "Would you still like to search for a specific review? (Any key to continue, 'X' to return to menu): ";
            cin >> input;

            if (input == "x" || input == "X")
            {
                cout << endl;
                cout << string(60, '-') << endl;
                choice = false;
            }
        }
        else
        {
            cout << string(60, '-') << endl;
            cout << "Invalid input. Please enter a number." << endl;
            cout << string(60, '-') << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

void searchReview()
{
    int option2 = 0;

    cout << "Search using algorithm: " << endl;

    while (option2 != 3)
    {
        system("cls");
        cout << endl;
        cout << "1. Binary Search" << endl;
        cout << "2. Linear Search" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << endl;
        cout << "Enter your choice (1-3): ";

        if (cin >> option2)
        {
            if (option2 == 1)
            {
                searchAndBinary();
            }
            else if (option2 == 2)
            {
                searchAndLinear();
            }
            else if (option2 == 3)
            {
                break;
            }
            else
            {
                cout << string(60, '-') << endl;
                cout << "Invalid choice. Please enter a valid number (1-3)." << endl;
                cout << string(60, '-') << endl;
            }
        }
        else
        {
            cout << string(60, '-') << endl;
            cout << "Invalid choice. Please enter a valid number (1-3)." << endl;
            cout << string(60, '-') << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main()
{
    system("cls");
    int menuOption = 0;

    while (menuOption != 4)
    {
        cout << string(60, '=') << endl;
        cout << endl;
        cout << "Array List Searching & Sorting Algorithms" << endl;
        cout << endl;
        cout << string(60, '-') << endl;
        cout << endl;
        cout << "1. Binary Search w/ Insertion Sort" << endl;
        cout << "2. Linear Search w/ Bubble Sort" << endl;
        cout << "3. Search Review" << endl;
        cout << "4. Exit" << endl;
        cout << endl;
        cout << string(60, '-') << endl;
        cout << "Enter your choice (1-4): ";

        if (cin >> menuOption)
        {
            cout << string(60, '-') << endl;
            cout << endl;

            if (menuOption == 1)
            {
                binary_insert();
            }
            else if (menuOption == 2)
            {
                linear_bubble();
            }
            else if (menuOption == 3)
            {
                searchReview();
            }
            else if (menuOption == 4)
            {
                break;
            }
            else
            {
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                cout << endl;
            }
        }
        else
        {
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
            cout << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    system("cls");
    cout << string(60, '=') << endl;
    cout << endl;
    cout << "Thank you! See you next time!" << endl;
    cout << endl;
    cout << string(60, '=') << endl;
    cin.ignore();
    cin.get();

    return 0;
}