#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../simpleFunctions/simpleFunctions.h"

#ifndef VDFPARSER_VDFPARSER2_H_
#define VDFPARSER_VDFPARSER2_H_

template <typename T>
ostream &operator<<(ostream &out, const vector<T> &v) {
    out << "{";
    size_t last = v.size() - 1;
    for (size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last) out << ", ";
    }
    out << "}";
    return out;
}

template <class T>
void safe_insert(std::vector<T> &vec, const size_t pos, const T arg) {
    if (vec.size() <= pos) vec.resize(pos);
    vec.insert(vec.begin() + pos, arg);
}

struct FileResult {
    string line;
    size_t len;
    string result;
    bool correct = false;
    FileResult() = default;
};

class VdfParser2 {
 private:
    string filePath;

    int openBracketPos = 0;
    int index = 0;
    bool found = false;
    vector<string> currentPath = {};

    FileResult isCorrectValue(char *line, size_t len, vector<string> path) {
        FileResult res;
        res.len = len;
        res.line = line;
        res.correct = false;

        if (found) return res;

        if (strstr(&line[0], "{")) {
            openBracketPos++;
            return res;
        }
        if (strstr(&line[0], "}")) {
            openBracketPos--;
            return res;
        }

        //! NEEDS CLEANUP!
        vector<string> str = SimpleFunctions::stringSplitByString(
          SimpleFunctions::replaceCharInString(
            SimpleFunctions::replaceCharInString(
              SimpleFunctions::removeCharRFromStart(
                SimpleFunctions::removeRCharFromString(line, '"'), '\t'),
              '\t',
              ' '),
            '\n',
            '\0'),
          "  ");

        cout << openBracketPos << "  " << currentPath.size() << endl;
        cout << str[0] << endl;
        // std::cout << str[0] << std::endl;
        // safe_insert(currentPath, openBracketPos, str[0]);
        // if (currentPath.size() <= openBracketPos) currentPath.resize(openBracketPos);
        currentPath.at(openBracketPos) = str[0];
        // currentPath.insert((currentPath.begin() + openBracketPos), str[0]);
        // if (currentPath.size() > 0 && currentPath.size() > openBracketPos) {
        //     // while (currentPath.size() > openBracketPos) {
        //         //
        //     // }
        // }

        // currentPath[index] = str[0];

        cout << currentPath << endl;
        cout << path << endl;
        cout << (currentPath == path) << endl;
        // cout << str[0].c_str() << " - " << strcmp(str[0].c_str(), path[openBracketPos].c_str())
        //      << " - " << path[openBracketPos].c_str() << endl;
        // if (strcmp(str[0].c_str(), path[openBracketPos].c_str()) == 0) {
        //     if (index == path.size() - 1) {
        //         res.len = len;
        //         res.line = line;
        //         res.result = str[1];
        //         res.correct = true;
        //         found = true;
        //     }
        //     index++;
        // }
        return res;
    }

 public:
    explicit VdfParser2(string filePath) { this->filePath = filePath; }

    FileResult readFile(string childPath) {
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
        fclose(fp);
        return fileResult;
    }

    void write(string childPath, string content) {
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
        // for (auto i : currentPath) {
        //     cout << i << endl;
        // }

        openBracketPos = 0;
        index = 0;
        found = false;
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
};
#endif  // VDFPARSER_VDFPARSER2_H_
