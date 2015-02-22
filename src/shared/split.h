#pragma once

#include <algorithm>
#include <string>
#include <vector>

//---------------------------------------------------------------------------------+
// int Split_NextPos                                                               |
// Find the index of the next occurrence from a set of delimiters in a string      |
//---------------------------------------------------------------------------------+
int Split_NextPos(const std::string &haystack, std::vector<char> delimiters) {
    std::vector<int> inds; int pos;
    for (unsigned int i = 0; i < delimiters.size(); i++) {
        pos = haystack.find(delimiters[i]);
        if (pos != std::string::npos) {
            inds.push_back(pos);
        }
    }
    if (inds.size() == 0) { return std::string::npos; }
    if (inds.size() == 1) { return pos; }

    pos = *min_element(inds.begin(), inds.end());
    return pos;
}

//---------------------------------------------------------------------------------+
// int Split_NextAntiPos                                                           |
// Find the index of the next occurrence from a set of anti-delimiters in a string |
//---------------------------------------------------------------------------------+
int Split_NextAntiPos(const std::string &haystack, std::vector<char> delimiters) {
    std::vector<int> inds; int pos;
    for (unsigned int i = 0; i < delimiters.size(); i++) {
        for (unsigned int j = 0; j < haystack.size(); j++) {
            if (find(delimiters.begin(), delimiters.end(), haystack[j]) != delimiters.end()) {
                inds.push_back(j);
            }
        }
    }
    if (inds.size() == 0) { return std::string::npos; }
    if (inds.size() == 1) { return inds[0]; }

    pos = *min_element(inds.begin(), inds.end());
    return pos;
}

//---------------------------------------------------------------------------------+
// std::vector<std::string> Split (multiple delimiters)                            |
// Split a string by a given set of delimiters using find and substr               |
//---------------------------------------------------------------------------------+
std::vector<std::string> Split(std::string haystack, std::vector<char> delimiters, bool anti) {
    std::vector<std::string> result;
    std::string part;

    int pos = anti ? Split_NextAntiPos(haystack, delimiters) : Split_NextPos(haystack, delimiters);
    while (pos != std::string::npos) {
        part = haystack.substr(0, pos);
        haystack = haystack.substr(pos + 1, std::string::npos);
        if (pos != 0 && part.length() != 0) {
            result.push_back(part);
        }

        pos = anti ? Split_NextAntiPos(haystack, delimiters) : Split_NextPos(haystack, delimiters);
    }
    if (haystack.length() != 0) {
        result.push_back(haystack);
    }

    return result;
}

//---------------------------------------------------------------------------------+
// std::vector<std::string> Split (single char delimiter)                          |
// Split a string by a given delimiter using find and substr                       |
//---------------------------------------------------------------------------------+
std::vector<std::string> Split(std::string haystack, char delimiter) {
    std::vector<std::string> result;
    std::string part;

    int pos = haystack.find(delimiter);
    while (pos != std::string::npos) {
        part = haystack.substr(0, pos);
        haystack = haystack.substr(pos + 1, std::string::npos);
        if (pos != 0 && part.length() != 0) {
            result.push_back(part);
        }
        pos = haystack.find(delimiter);
    }
    if (haystack.length() != 0) {
        result.push_back(haystack);
    }

    return result;
}

//---------------------------------------------------------------------------------+
// std::vector<std::string> Split (single const char* delimiter)                   |
// Split a string by a given delimiter using find and substr                       |
//---------------------------------------------------------------------------------+
std::vector<std::string> Split(std::string haystack, const char* delimiter) {
    std::vector<std::string> result;
    std::string part;

    int pos = haystack.find(delimiter);
    while (pos != std::string::npos) {
        part = haystack.substr(0, pos);
        haystack = haystack.substr(pos + 1, std::string::npos);
        if (pos != 0 && part.length() != 0) {
            result.push_back(part);
        }
        pos = haystack.find(delimiter);
    }
    if (haystack.length() != 0) {
        result.push_back(haystack);
    }

    return result;
}

//---------------------------------------------------------------------------------+
// std::vector<std::string> Split (single std::string delimiter)                   |
// Split a string by a given delimiter using find and substr                       |
//---------------------------------------------------------------------------------+
std::vector<std::string> Split(std::string haystack, std::string delimiter) {
    std::vector<std::string> result;
    std::string part;

    int pos = haystack.find(delimiter);
    while (pos != std::string::npos) {
        part = haystack.substr(0, pos);
        haystack = haystack.substr(pos + 1, std::string::npos);
        if (pos != 0 && part.length() != 0) {
            result.push_back(part);
        }
        pos = haystack.find(delimiter);
    }
    if (haystack.length() != 0) {
        result.push_back(haystack);
    }

    return result;
}
