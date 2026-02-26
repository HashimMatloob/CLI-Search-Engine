#include "Searcher.h"

void Searcher::performSearch(string query, unordered_map<string, vector<FileInfo>>& wordIndex) {
    searchHistory.push_back(query);

    cout << "\n---------------------------------------\n";
    cout << "Searching for: \"" << query << "\"\n";

    vector<string> searchWords;
    string word;
    stringstream queryStream(query);

    while(queryStream >> word) {
        word = Utils::toLowerCase(word);
        string cleanWord = Utils::cleanString(word);

        if(cleanWord.empty() || Utils::isCommonWord(cleanWord)) continue;

        cleanWord = Utils::simplifyWord(cleanWord);
        searchWords.push_back(cleanWord);
    }

    if(searchWords.empty()) {
        cout << "No valid search words found.\n";
        return;
    }

    unordered_map<string, int> fileScores;
    for(string searchWord : searchWords) {
        if(wordIndex.find(searchWord) != wordIndex.end()) {
            for(int i = 0; i < wordIndex[searchWord].size(); i++) {
                FileInfo info = wordIndex[searchWord][i];
                fileScores[info.filename] += info.count;
            }
        }
    }

    if(fileScores.empty()) {
        cout << "No results found.\n";
        return;
    }

    vector<pair<string, int>> results;
    for(auto &entry : fileScores) {
        results.push_back({entry.first, entry.second});
    }

    sort(results.begin(), results.end(), [](pair<string, int> a, pair<string, int> b) {
        return a.second > b.second;
    });

    cout << "Found in " << results.size() << " file(s):\n";

    int numResults;
    cout << "How many results to show? ";
    cin >> numResults;

    if(cin.fail() || numResults < 0) {
        cout << "Please enter a positive number.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    if(numResults > results.size()) numResults = results.size();
    if(numResults == 0) {
        cout << "No results to show.\n";
        return;
    }

    cout << "\nTop " << numResults << " results:\n";

    for(int i = 0; i < numResults; i++) {
        string filename = results[i].first;
        int score = results[i].second;

        cout << "\n" << (i+1) << ". " << filename;
        cout << " (found " << score << " times)\n";

        ifstream file(filename);
        if(!file) {
            cout << "   Could not open file for preview.\n";
            continue;
        }
        cout << "   Preview:\n";

        string line;
        int linesShown = 0;
        int lineNumber = 0;

        while(getline(file, line) && linesShown < 2) {
            lineNumber++;
            string lowerLine = Utils::toLowerCase(line);
            bool hasSearchWord = false;
            for(string searchWord : searchWords) {
                if(lowerLine.find(searchWord) != string::npos) {
                    hasSearchWord = true;
                    break;
                }
            }

            if(hasSearchWord) {
                if(line.length() > 100) line = line.substr(0, 97) + "...";
                cout << "   Line " << lineNumber << ": " << line << "\n";
                linesShown++;
            }
        }
        file.close();
        if(linesShown == 0) cout << "   (No matching lines in preview)\n";
    }
}

void Searcher::showHistory() {
    cout << "\nSearch History:\n";
    if(searchHistory.empty()) {
        cout << "No searches yet.\n";
    } else {
        for(int i = 0; i < searchHistory.size(); i++) {
            cout << (i+1) << ". " << searchHistory[i] << "\n";
        }
    }
}
