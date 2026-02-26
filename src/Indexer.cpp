#include "Indexer.h"

Indexer::Indexer() {
    // txt files in our project folder
    allFiles = {"article1.txt", "article2.txt", "fruits.txt"};
}

unordered_map<string, vector<FileInfo>>& Indexer::getIndex() {
    return wordIndex;
}

vector<string> Indexer::getFileList() {
    return allFiles;
}

void Indexer::indexWord(string word, string filename) {
    if(wordIndex.find(word) == wordIndex.end()) {
        wordIndex[word] = {{filename, 1}};
    } else {
        bool fileFound = false;
        for(int i = 0; i < wordIndex[word].size(); i++) {
            if(wordIndex[word][i].filename == filename) {
                wordIndex[word][i].count++;
                fileFound = true;
                break;
            }
        }
        if(!fileFound) {
            wordIndex[word].push_back({filename, 1});
        }
    }
}

void Indexer::showFilePreviews() {
    cout << "Reading files:\n";
    for(string filename : allFiles) {
        ifstream file(filename);
        if(!file) {
            cout << "Error: Cannot open " << filename << "\n";
            continue;
        }
        cout << "\nFile: " << filename << "\n";
        cout << "----------------------------\n";
        string line;
        int linesShown = 0;
        while(getline(file, line) && linesShown < 10) {
            cout << line << "\n";
            linesShown++;
        }
        if(linesShown >= 10) cout << "... (showing first 10 lines only)\n";
        file.close();
    }
}

void Indexer::buildIndex() {
    cout << "\n\nIndexing files...\n";
    for(string filename : allFiles) {
        ifstream file(filename);
        if(!file) {
            cout << "Cannot index " << filename << " (file not found)\n";
            continue;
        }
        cout << "Indexing: " << filename << "\n";

        string line;
        int wordsIndexed = 0;

        while(getline(file, line)) {
            // Lowercase entire line first
            line = Utils::toLowerCase(line);

            // Replace punctuation with space
            for(int i = 0; i < line.length(); i++) {
                char c = line[i];
                if(c == '.' || c == ',' || c == '!' || c == '?' || c == ';' || c == ':') {
                    line[i] = ' ';
                }
            }

            stringstream lineStream(line);
            string word;
            while(lineStream >> word) {
                if(Utils::isCommonWord(word)) continue;

                word = Utils::simplifyWord(word);
                if(!word.empty()) {
                    indexWord(word, filename);
                    wordsIndexed++;
                }
            }
        }
        file.close();
        cout << "   -> Indexed " << wordsIndexed << " words\n";
    }
    cout << "\nIndexing complete!\n";
}

int Indexer::getUniqueWordCount() {
    return wordIndex.size();
}

int Indexer::getTotalOccurrences() {
    int total = 0;
    for(auto &entry : wordIndex) {
        for(int i = 0; i < entry.second.size(); i++) {
            total += entry.second[i].count;
        }
    }
    return total;
}
