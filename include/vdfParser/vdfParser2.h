#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../simpleFunctions/simpleFunctions.h"

#ifndef VDFPARSER_VDFPARSER2_H_
#define VDFPARSER_VDFPARSER2_H_

class VdfParser2 {
    string filePath;
    FILE *fp;

 public:
    explicit VdfParser2(string filePath) {
        this->filePath = filePath;
        fp = fopen(filePath.c_str(), "r");
        if (fp == NULL) {
            printf("Error! opening file");
            exit(1);
        }
    }

    void close() { fclose(fp); }

    string readFile(string childPath, bool autoClose = true) {
        vector<string> path = SimpleFunctions::stringSplitByChar(childPath, '/');
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        int openBracketPos = 0;
        int index = 0;
        string result;
        while ((read = getline(&line, &len, fp)) != -1) {
            if (line == NULL) break;
            bool isBracket = false;
            if (strstr(&line[0], "{")) {
                isBracket = true;
                openBracketPos++;
            }
            if (strstr(&line[0], "}")) {
                isBracket = true;
                openBracketPos--;
            }

            if (!isBracket) {
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
                if (strcmp(str[0].c_str(), path[openBracketPos].c_str()) == 0) {
                    if (index == path.size() - 1) {
                        result = str[1];
                        break;
                    }
                    index++;
                }
            }
        }
        if (autoClose) {
            close();
        } else {
            cout << "Please call the close function when done!" << endl;
        }
        return result;
    }

    void write(string path, string content) {}
};
#endif  // VDFPARSER_VDFPARSER2_H_
