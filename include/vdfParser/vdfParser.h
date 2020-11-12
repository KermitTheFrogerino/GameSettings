#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

#ifndef VDFPARSER_VDFPARSER_H_
#define VDFPARSER_VDFPARSER_H_

using namespace std;

struct FileResult {
    string line;
    size_t len;
    string result;
    bool correct = false;
    vector<string> formattedLine;
    bool isOpenBracket = false;
    bool isClosedBracket = false;
};

struct VDFResult {
    map<string, string> attributes;
    map<string, VDFResult> childs;
};

class VdfParser {
 private:
    string filePath;
    int openBracketPos = 0;
    int index = 0;
    bool found = false;
    vector<string> currentPath;

    FileResult isCorrectValue(char *line,
                              size_t len,
                              vector<string> path,
                              bool returnOnFound = true);

 public:
    explicit VdfParser(string filePath);

    FileResult readFile(string childPath);

    VDFResult getVectorFromPath(string childPath);

    void write(string childPath, string content);
};
#endif  // VDFPARSER_VDFPARSER_H_
