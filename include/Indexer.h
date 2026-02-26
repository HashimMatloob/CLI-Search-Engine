#ifndef INDEXER_H
#define INDEXER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "Utils.h"

using namespace std;

struct FileInfo {
    string filename;
    int count;
};

class Indexer {
private:
    // The main data structure
    unordered_map<string, vector<FileInfo>> wordIndex;
    vector<string> allFiles;

    void indexWord(string word, string filename);

public:
    Indexer(); // Constructor
    void addFile(string filename);
    void buildIndex();
    void showFilePreviews(); // Moved the preview logic here

    // Getters
    unordered_map<string, vector<FileInfo>>& getIndex(); // Return reference to index
    int getUniqueWordCount();
    int getTotalOccurrences();
    vector<string> getFileList();
};

#endif
