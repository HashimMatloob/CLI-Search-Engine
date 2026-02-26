#ifndef SEARCHER_H
#define SEARCHER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "Indexer.h"
#include "Utils.h"

using namespace std;

class Searcher {
private:
    vector<string> searchHistory;

public:
    // passing the map by reference so we don't copy the whole database
    void performSearch(string query, unordered_map<string, vector<FileInfo>>& wordIndex);
    void showHistory();
};

#endif
