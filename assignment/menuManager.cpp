#include "csv_handler2.hpp"
#include "menuManager.hpp"

const int MAX_SIZE = 21000;

menuManager::menuManager()
{
    reviews = new string[MAX_SIZE];
    ratings = new string[MAX_SIZE];
    reviewCount = 0;
}

void menuManager::resetArrays()
{
    delete[] reviews;
    delete[] ratings;
    reviews = new string[MAX_SIZE];
    ratings = new string[MAX_SIZE];
    reviewCount = 0;
}

int menuManager::binary_insert()
{
    system("cls");

    resetArrays();

    // New Handler Object
    csvHandler handler1;

    // Load review CSV file
    ifstream file("tripadvisor_hotel_reviews.csv");
    if (!file.is_open())
    {
        cout << string(60, '-') << endl;
        cerr << "CSV file for Tripadvisor Hotel Reviews Missing!" << endl;
        cout << string(60, '-') << endl;
        cin.ignore();
        cin.get();
        return 0;
    }

    if (handler1.positiveCount == 0 || handler1.negativeCount == 0)
    {
        cout << string(60, '-') << endl;
        cerr << "Text file for Positive & Negative Word Comparision Missing!" << endl;
        cout << string(60, '-') << endl;
        cin.ignore();
        cin.get();
        return 0;
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

        reviews[reviewCount] = review;
        ratings[reviewCount] = rating;

        // Print review and rating
        cout << "Review: " << review << endl;
        cout << "Rating: " << rating << endl;
        cout << endl;

        // Count positive and negative words in the review
        handler1.countSentimentWordsUsingBinarySearch(review);

        cout << endl;
        cout << string(60, '*') << endl;
        cout << endl;

        reviewCount++;
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

int menuManager::linear_bubble()
{
    system("cls");

    resetArrays();

    // New Handler Object
    csvHandler handler2;

    ifstream file("tripadvisor_hotel_reviews.csv");
    if (!file.is_open())
    {
        cout << string(60, '-') << endl;
        cerr << "CSV file for Tripadvisor Hotel Reviews Missing!" << endl;
        cout << string(60, '-') << endl;
        cin.ignore();
        cin.get();
        return 0;
    }

    if (handler2.positiveCount == 0 || handler2.negativeCount == 0)
    {
        cout << string(60, '-') << endl;
        cerr << "Text file for Positive & Negative Word Comparision Missing!" << endl;
        cout << string(60, '-') << endl;
        cin.ignore();
        cin.get();
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

        reviews[reviewCount] = review;
        ratings[reviewCount] = rating;

        // Print review and rating
        cout << "Review: " << review << endl;
        cout << "Rating: " << rating << endl;
        cout << endl;

        // Count positive and negative words in the review
        handler2.countSentimentWordsusingLinearSearch(review);

        

        cout << endl;
        cout << string(60, '*') << endl;
        cout << endl;

        reviewCount++;
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

void menuManager::searchAndBinary(string *reviews, string *ratings, int reviewCount)
{
    csvHandler handler3;
    bool choice = true;
    string input;

    while (choice)
    {
        system("cls");

        int recordIndex = 0;

        cout << "Enter the index of the record you want to analyze (1 - " << reviewCount - 1 << "): ";

        if (cin >> recordIndex)
        {
            if (recordIndex < 1 || recordIndex >= reviewCount)
            {
                cout << endl;
                cout << string(60, '-') << endl;
                cout << "The index is out of the range! Press 'Enter' to try again." << endl;
                ;
                cout << string(60, '-') << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }
            else
            {
                cout << endl;
                cout << string(60, '-') << endl;

                handler3.searchRecordByIndexBS(reviews, ratings, recordIndex, reviewCount);

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

void menuManager::searchAndLinear(string *reviews, string *ratings, int reviewCount)
{
    csvHandler handler3;
    bool choice = true;
    string input;

    while (choice)
    {
        system("cls");

        int recordIndex = 0;

        cout << "Enter the index of the record you want to analyze (1 - " << reviewCount - 1 << "): ";

        if (cin >> recordIndex)
        {
            if (recordIndex < 1 || recordIndex >= reviewCount)
            {
                cout << endl;
                cout << string(60, '-') << endl;
                cout << "The index is out of the range! Press 'Enter' to try again." << endl;
                ;
                cout << string(60, '-') << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }
            else
            {
                cout << endl;
                cout << string(60, '-') << endl;

                handler3.searchRecordByIndexLS(reviews, ratings, recordIndex, reviewCount);

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

void menuManager::searchReview()
{
    if (reviewCount == 0)
    {
        system("cls");
        cout << string(60, '-') << endl;
        cout << "No reviews available to analyze." << endl
             << "Please run 'Binary Search & Insertion Sort' or 'Linear Search & Bubble Sort' options at least once." << endl;
        cout << string(60, '-') << endl;
        cin.ignore();
        cin.get();
        return;
    }

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
                searchAndBinary(reviews, ratings, reviewCount);
            }
            else if (option2 == 2)
            {
                searchAndLinear(reviews, ratings, reviewCount);
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

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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