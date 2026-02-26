#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

class Utils {
public:
    // Static functions so we don't need to create an object to use them
    static bool isCommonWord(string word);
    static string simplifyWord(string word);
    static string toLowerCase(string word);
    static string cleanString(string word);

private:
    static string commonWords[];
};

#endif
