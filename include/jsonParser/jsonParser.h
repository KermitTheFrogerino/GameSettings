#include <iostream>
#include <vector>
#include "../simpleFunctions/simpleFunctions.h"

#ifndef JSONPARSER_JSONPARSER_H_
#define JSONPARSER_JSONPARSER_H_

using namespace std;

class MyJsonParser {
 private:
    char const *dir;
    vector<char *> pathSplit;

 public:
    MyJsonParser(char const *dir, char path[]) {
        this->dir = dir;
        char *item;
        int index = 0;
        while ((item = strtok_r(path, "/", &path))) {
            pathSplit.push_back(item);
            index++;
        }
        for (size_t i = 0; i < pathSplit.size(); i++) {
            cout << " " << pathSplit[i];
        }
        // list<char *>::iterator it;
        // for (it = pathSplit.begin(); it != pathSplit.end(); ++it) {
        //     cout << " " << *it;
        // }
        // cout << pathSplit.size();
        printf("\n\n");
    }

    void parse() {
        FILE *fp;
        if ((fp = fopen(dir, "r")) == NULL) {
            printf("Error! opening file");
            exit(1);
        }
        // Gets the size of the file
        int64_t size;
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char *c = reinterpret_cast<char *>(malloc(sizeof(char) * size));

        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        int openBracketPos = 0;
        bool lastLineOpenBracket = false;
        int index = 2;
        int keyPos = 0;

        while ((read = getline(&line, &len, fp)) != -1) {
            bool setLastOpenBracket = false;
            int length = strlen(SimpleFunctions::removeSpaces(line));
            // if (length < 0) length = 0;
            // cout << line << "\n";
            // cout << line[length] << "yeet" << length;
            // cout << "\n\n";
            char *character = &line[0];

            if (strstr(character, "{")) {
                openBracketPos++;
                lastLineOpenBracket = true;
                // cout << openBracketPos << line;
            }

            // cout << openBracketPos << SimpleFunctions::removeSpaces(line);
            cout << openBracketPos << "  " << character << "  " << line;
            // cout << index;
            // if (openBracketPos == index) {
            //     // cout << pathSplit[index - 2] << line;
            //     if (strstr(line, SimpleFunctions::surroundChar(
            //                        "\"", pathSplit[index - 2], "\":"))) {
            //         // cout << line;
            //         index++;
            //     }
            // }

            // if (openBracketPos == pathSplit.size()) {
            //     cout << openBracketPos << line;
            //     // if (strstr(line, pathSplit[openBracketPos - 1])) {
            //     //     cout << "pathSplit[openBracketPos - 1]";
            //     // }
            // }

            if (strstr(character, "}") || strstr(character, "},")) {
                // cout << openBracketPos << line;
                openBracketPos--;
            }

            lastLineOpenBracket = setLastOpenBracket;
        }
        printf("\n");
        fclose(fp);
    }
};
#endif  // JSONPARSER_JSONPARSER_H_
