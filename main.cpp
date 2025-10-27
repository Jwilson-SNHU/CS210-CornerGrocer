#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm> // for transform

using namespace std;

// GroceryTracker class handles loading data, counting items, and displaying results
class GroceryTracker {
private:
    map<string, int> itemFrequency;

public:
    // Load data file and build frequency map
    void LoadFile(const string &filename) {
        ifstream inputFile(filename);
        if (!inputFile) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string item;
        while (inputFile >> item) {
            // convert to lowercase for case-insensitive counting
            transform(item.begin(), item.end(), item.begin(), ::tolower);
            itemFrequency[item]++;
        }

        inputFile.close();

        // Save to frequency.dat for backup
        ofstream backupFile("frequency.dat");
        for (auto &pair : itemFrequency) {
            backupFile << pair.first << " " << pair.second << endl;
        }
        backupFile.close();
    }

    // Menu Option 1: Search for a specific item frequency
    void GetItemFrequency() {
        string searchItem;
        cout << "Enter item to search: ";
        cin >> searchItem;
        transform(searchItem.begin(), searchItem.end(), searchItem.begin(), ::tolower);

        if (itemFrequency.count(searchItem)) {
            cout << searchItem << " appears " << itemFrequency[searchItem] << " time(s)." << endl;
        } else {
            cout << searchItem << " was not found in the list." << endl;
        }
    }

    // Menu Option 2: Print all item frequencies
    void PrintAllFrequencies() {
        cout << "\nItem Frequencies:\n";
        for (auto &pair : itemFrequency) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    // Menu Option 3: Print histogram of item frequencies
    void PrintHistogram() {
        cout << "\nHistogram:\n";
        for (auto &pair : itemFrequency) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; i++) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

int main() {
    GroceryTracker tracker;
    tracker.LoadFile("CS210_Project_Three_Input_File.txt"); // Load data

    int choice = 0;

    while (choice != 4) {
        cout << "\n===== Corner Grocer Menu =====\n";
        cout << "1. Search for an item\n";
        cout << "2. Display all item frequencies\n";
        cout << "3. Display histogram\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice)) { // Input validation
            cin.clear();           // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
        }

        switch (choice) {
            case 1:
                tracker.GetItemFrequency();
                break;
            case 2:
                tracker.PrintAllFrequencies();
                break;
            case 3:
                tracker.PrintHistogram();
                break;
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    }

    return 0;
}
