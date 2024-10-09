#include "csv_handler2.hpp"
#include "menuManager.hpp"
using namespace std;

int main()
{
    menuManager menu;

    int menuOption = 0;

    while (menuOption != 4)
    {
        system("cls");
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
                menu.binary_insert();
            }
            else if (menuOption == 2)
            {
                menu.linear_bubble();
            }
            else if (menuOption == 3)
            {
                menu.searchReview();
            }
            else if (menuOption == 4)
            {
                break;
            }
            else
            {
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                cout << endl;

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
            }
        }
        else
        {
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
            cout << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
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