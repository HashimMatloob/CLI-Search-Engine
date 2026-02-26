#include "Utils.h"

string Utils::commonWords[] = {
    "the", "is", "and", "of", "to", "in", "on", "for", "with",
    "a", "an", "are", "was", "were", "as", "at", "be", "by",
    "it", "or", "that", "this", "which", "you", "he", "she",
    "they", "but", "not", "what", "all", "when", "where",
    "will", "would", "can", "could"
};

bool Utils::isCommonWord(string word) {
    for(string cw : commonWords) {
        if(word == cw) return true;
    }
    return false;
}

string Utils::simplifyWord(string word) {
    int length = word.length();
    if(length > 4 && word.substr(length-3) == "ing") return word.substr(0, length-3);
    if(length > 3 && word.substr(length-2) == "ed") return word.substr(0, length-2);
    if(length > 3 && word[length-1] == 's') return word.substr(0, length-1);
    return word;
}

string Utils::toLowerCase(string word) {
    for(int i = 0; i < word.length(); i++) {
        word[i] = tolower(word[i]);
    }
    return word;
}

string Utils::cleanString(string word) {
    string clean = "";
    for(int i = 0; i < word.length(); i++) {
        char c = word[i];
        if((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            clean += c;
        }
    }
    return clean;
}
