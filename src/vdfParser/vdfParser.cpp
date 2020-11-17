#include "vdfParser.hpp"
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>
#include "../func/func.hpp"

using namespace std;

VdfParser::VdfParser(string filePath) { this->filePath = filePath; }

VdfParser::FileResult VdfParser::isCorrectValue(char *line, size_t len, vector<string> path) {
    FileResult res;
    res.len = len;
    res.line = line;

    if (strstr(&line[0], "{")) {
        openBracketPos++;
        return res;
    }
    if (strstr(&line[0], "}")) {
        openBracketPos--;
        return res;
    }

    string noQuotes = Func::removeRCharFromString(line, '"');
    string noStartTabs = Func::removeCharRFromStart(noQuotes, '\t');
    string noTabs = Func::replaceCharInString(noStartTabs, '\t', ' ');
    string noNewLine = Func::removeRCharFromString(noTabs, '\n');
    res.formattedLine = Func::stringSplitByString(noNewLine, "  ");
    // Resize the vector to the size of the path vector
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
    res.path = currentPath;
    if (openBracketPos + 1 < path.size() || res.formattedLine.size() < 2) return res;
    if (Func::vectorMatch(path, currentPath, false)) {
        // Return if is comment
        std::regex reg = std::regex("(?:/\\*(?:[^*]|(?:\\*+[^*/]))*\\*+/)|(?://.*)");
        if (regex_match(res.formattedLine[0], reg)) return res;
        if (regex_match(res.formattedLine[1], reg)) return res;
        res.correct = true;
    }
    return res;
}

/**
 * @brief Returns an map from the file and excludes attributes that don't match the exact path
 *
 * @param childPath The path to the items. Ex: "Parent/Child/Collection". Can't start with "/"
 * @return map<string, string>
 */
map<string, string> VdfParser::getFromPath(string childPath) {
    FILE *fp = std::fopen(filePath.c_str(), "r");
    if (fp == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    vector<string> path = Func::stringSplitByChar(childPath, '/');
    char *line = NULL;
    size_t len = 0;
    map<string, string> vdfResult;
    while (getline(&line, &len, fp) != -1) {
        if (line == NULL) break;
        FileResult res = isCorrectValue(line, len, path);
        if (!res.correct || res.path.empty()) continue;
        // Shorten the vector to delta path
        res.path = vector<string>(res.path.begin() + path.size(), res.path.end());
        string key;
        for (size_t i = 0; i < res.path.size(); i++) {
            key += res.path[i] + (i + 1 == res.path.size() ? "" : "/");
        }
        // If the path is pointing to an attribute, set the key to the attribute name
        if (key.empty()) key = path.back();
        vdfResult.insert(make_pair(key, res.formattedLine[1]));
    }
    openBracketPos = 0;
    currentPath.clear();
    std::fclose(fp);
    return vdfResult;
}

/**
 * @brief Writes content to an existing attribute
 *
 * @param childPath The path to the attribute. Ex: "Parent/Child/attr". Can't start with "/"
 * @param content The string to set
 */
void VdfParser::replaceInFile(string childPath, string content) {
    FILE *fp = std::fopen(filePath.c_str(), "r");
    if (fp == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    vector<string> path = Func::stringSplitByChar(childPath, '/');
    vector<FileResult> fileResults;
    char *line = NULL;
    size_t len = 0;
    // Gather all lines into a vector
    while (getline(&line, &len, fp) != -1) {
        if (line == NULL) break;
        FileResult res = isCorrectValue(line, len, path);
        if (res.correct) {
            // Replace the original value with the new content
            size_t pos =  res.line.find(res.formattedLine[1].c_str());
            res.line.replace(pos, res.formattedLine[1].size(), content);
        }
        fileResults.push_back(res);
    }
    openBracketPos = 0;
    currentPath.clear();
    std::fclose(fp);

    // Reopen the file with write permissions and write
    fp = std::fopen(filePath.c_str(), "w");
    if (fp == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    for (FileResult res : fileResults) {
        fputs(res.line.c_str(), fp);
    }
    std::fclose(fp);
}
