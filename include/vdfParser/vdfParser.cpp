#include "vdfParser.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../simpleFunctions/simpleFunctions.h"

using namespace std;

VdfParser::VdfParser(string filePath) { this->filePath = filePath; }

FileResult VdfParser::isCorrectValue(char *line,
                                     size_t len,
                                     vector<string> path,
                                     bool returnOnFound) {
    FileResult res;
    res.len = len;
    res.line = line;

    if (found) return res;
    if (strstr(&line[0], "{")) {
        openBracketPos++;
        res.isOpenBracket = true;
        return res;
    }
    if (strstr(&line[0], "}")) {
        openBracketPos--;
        res.isClosedBracket = true;
        return res;
    }

    string noQuotes = SimpleFunctions::removeRCharFromString(line, '"');
    string noStartTabs = SimpleFunctions::removeCharRFromStart(noQuotes, '\t');
    string noTabs = SimpleFunctions::replaceCharInString(noStartTabs, '\t', ' ');
    string noNewLine = SimpleFunctions::replaceCharInString(noTabs, '\n', '\0');
    res.formattedLine = SimpleFunctions::stringSplitByString(noNewLine, "  ");
    if (openBracketPos + 1 < currentPath.size()) {
        while (openBracketPos + 1 < currentPath.size()) {
            currentPath.pop_back();
        }
        currentPath.resize(openBracketPos + 1);
    }
    if (openBracketPos >= currentPath.size()) {
        currentPath.resize(openBracketPos + 1);
    }
    currentPath.at(openBracketPos) = res.formattedLine[0];
    if (openBracketPos + 1 != path.size()) return res;
    if (SimpleFunctions::workingVectorEqual(path, currentPath)) {
        res.len = len;
        res.line = line;
        res.result = res.formattedLine[1];
        res.correct = true;
        found = returnOnFound;
    }
    return res;
}

FileResult VdfParser::readFile(string childPath) {
    FILE *fp = fopen(filePath.c_str(), "r");
    if (fp == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    vector<string> path = SimpleFunctions::stringSplitByChar(childPath, '/');
    char *line = NULL;
    size_t len = 0;
    FileResult fileResult;
    while (getline(&line, &len, fp) != -1) {
        if (line == NULL) break;
        FileResult res = isCorrectValue(line, len, path);
        if (res.correct) {
            fileResult = res;
            break;
        }
    }
    openBracketPos = 0;
    index = 0;
    found = false;
    currentPath.clear();
    fclose(fp);
    return fileResult;
}

VDFResult VdfParser::getVectorFromPath(string childPath) {
    FILE *fp = fopen(filePath.c_str(), "r");
    if (fp == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    vector<string> path = SimpleFunctions::stringSplitByChar(childPath, '/');
    char *line = NULL;
    size_t len = 0;
    int initopenBracketPos;
    bool isCorrect = false;
    bool isNextLine = false;
    VDFResult vdfResult;
    vector<string> strPath;
    while (getline(&line, &len, fp) != -1) {
        if (line == NULL) break;
        FileResult res = isCorrectValue(line, len, path, false);
        if (isCorrect) {
            // Checks if the next line is a bracket
            if (isNextLine) {
                isNextLine = false;
                if (!res.isOpenBracket) {
                    cout << "ERROR! DOES NOT CONTAIN CHILDREN!" << endl;
                    exit(1);
                }
                // -1 because of the bracket check adding 1 to openBracketPos before this
                initopenBracketPos = openBracketPos - 1;
                cout << "init pos: " << initopenBracketPos << endl;
            }
            // Checks if the line isn't a bracket
            if (res.isOpenBracket) {
                continue;
            }
            if (res.isClosedBracket) {
                cout << strPath << endl;
                if (openBracketPos - 1 == initopenBracketPos) strPath.clear();
                continue;
            }
            if (res.isClosedBracket && openBracketPos - 1 == initopenBracketPos) break;
            if (res.formattedLine.size() > 1) {
                vdfResult.attributes[res.formattedLine[0]] = res.formattedLine[1];
            } else {
                strPath.push_back(res.formattedLine[0]);
                // vdfResult.childs[res.formattedLine[0]] = VDFResult();
            }

            // cout << openBracketPos << "  -  "
            //      << res.formattedLine[0] + ": " +
            //           (res.formattedLine.size() > 1 ? res.formattedLine[1] : "")
            //      << endl;
        }
        if (res.correct) {
            isCorrect = res.correct;
            isNextLine = true;
        }
    }
    // for (auto ee : vdfResult.attributes) {
    //     cout << ee.first << ": " << endl;
    // }
    openBracketPos = 0;
    index = 0;
    found = false;
    fclose(fp);

    return vdfResult;
}

void VdfParser::write(string childPath, string content) {
    FILE *fp = fopen(filePath.c_str(), "r");
    if (fp == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    vector<string> path = SimpleFunctions::stringSplitByChar(childPath, '/');
    vector<FileResult> fileResults;
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, fp) != -1) {
        if (line == NULL) break;
        FileResult res = isCorrectValue(line, len, path);
        if (res.correct) {
            if (!content.ends_with('\"')) content += "\"";
            res.line.replace(res.line.find(res.result.c_str()), res.line.size() - 1, content);
        }
        fileResults.push_back(res);
    }
    openBracketPos = 0;
    index = 0;
    found = false;
    currentPath.clear();
    fclose(fp);

    fp = fopen(filePath.c_str(), "w");
    if (fp == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    bool lastCorrect = false;
    for (auto res : fileResults) {
        // Adds a new line to the begining of the line after the modified line
        if (lastCorrect) {
            res.line = "\n" + res.line;
            lastCorrect = false;
        }
        if (res.correct == true) lastCorrect = true;
        fputs(res.line.c_str(), fp);
    }
    fclose(fp);
}
