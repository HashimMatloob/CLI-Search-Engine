#include <iostream>
#include <string>
#include "Indexer.h"
#include "Searcher.h"

using namespace std;

int main() {
    cout << "Starting console based search engine...\n\n";

    // 1. Create Objects
    Indexer myIndexer;
    Searcher mySearcher;

    // 2. Initial Setup (Preview and Indexing)
    myIndexer.showFilePreviews();
    myIndexer.buildIndex();

    // 3. Stats
    cout << "\nStatistics:\n";
    cout << "Unique words: " << myIndexer.getUniqueWordCount() << "\n";
    cout << "Total word occurrences: " << myIndexer.getTotalOccurrences() << "\n";

    // 4. Main Menu Loop
    while(true) {
        cout << "\n================== MENU ==================\n";
        cout << "1. Search\n";
        cout << "2. Show indexed files\n";
        cout << "3. Show unique word count\n";
        cout << "4. Show search history\n";
        cout << "5. Exit\n";
        cout << "Choose an option (1-5): ";

        int choice;
        cin >> choice;

        if(choice == 1) {
            string query;
            cout << "\nEnter search query: ";
            getline(cin, query); // Clear buffer
            getline(cin, query); // Get actual input

            // Pass the index data to the searcher
            mySearcher.performSearch(query, myIndexer.getIndex());
        }
        else if(choice == 2) {
            cout << "\nIndexed files:\n";
            vector<string> files = myIndexer.getFileList();
            for(string filename : files) {
                cout << "- " << filename << "\n";
            }
        }
        else if(choice == 3) {
            cout << "\nUnique words in index: " << myIndexer.getUniqueWordCount() << "\n";
        }
        else if(choice == 4) {
            mySearcher.showHistory();
        }
        else if(choice == 5) {
            cout << "\nbye twin\n";
            break;
        }
        else {
            cout << "Invalid choice. Please enter 1-5.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
    return 0;
}
