#include <any>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "../simpleFunctions/simpleFunctions.h"

#ifndef JSONPARSER_JSONPARSER_H_
#define JSONPARSER_JSONPARSER_H_

using namespace std;

/*
 * @param `dir` is the path to the .json file
 * @param `path[]` is the json path which is divided by every /
 */
class MyJsonParser {
 private:
    const string *dir;
    vector<string> pathSplit;

 public:
    MyJsonParser(const string *dir, string path) {
        this->dir = dir;
        char *item;
        int index = 0;
        pathSplit = SimpleFunctions::stringSplit(path);
        for (auto item : pathSplit) {
            cout << item << endl;
        }
        cout << endl;
    }

    ~MyJsonParser() { delete dir; }

    void parse() {
        FILE *fp = fopen(dir->c_str(), "r");
        if (fp == NULL) {
            printf("Error! opening file");
            exit(1);
        }

        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        int openBracketPos = 0;
        bool lastLineOpenBracket = false;
        int index = 2;
        int keyPos = 0;

        std::map<std::string, std::any> output;

        vector<string> location = {};

        while ((read = getline(&line, &len, fp)) != -1) {
            if (line == NULL) continue;
            bool setLastOpenBracket = false;
            int length = strlen(SimpleFunctions::removeSpaces(line));
            char *character = &line[0];
            cout << character;

            if (strstr(character, "{")) {
                openBracketPos++;
                setLastOpenBracket = true;
                string *item = new string
                item = *character;
                location.insert(item);
                cout << item << endl;
            }

            // cout << openBracketPos << endl;

            if (strstr(character, "}") || strstr(character, "}")) {
                openBracketPos--;
            }

            lastLineOpenBracket = setLastOpenBracket;
            cout << endl;
        }
        // cout << "\n" << endl;

        // for (auto item : location) {
        //     cout << item << endl;
        // }

        cout << endl;
        fclose(fp);
    }
};
#endif  // JSONPARSER_JSONPARSER_H_
