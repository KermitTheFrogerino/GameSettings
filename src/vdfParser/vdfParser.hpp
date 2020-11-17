#include <map>
#include <string>
#include <vector>

#ifndef SRC_VDFPARSER_VDFPARSER_HPP_
#define SRC_VDFPARSER_VDFPARSER_HPP_

using namespace std;

class VdfParser {
 private:
    struct FileResult {
        string line;
        size_t len;
        bool correct = false;
        vector<string> formattedLine;
        vector<string> path;
    };
    string filePath;
    int openBracketPos = 0;
    vector<string> currentPath;

    VdfParser::FileResult isCorrectValue(char *line, size_t len, vector<string> path);

 public:
    explicit VdfParser(string filePath);

    map<string, string> getFromPath(string childPath);

    void replaceInFile(string childPath, string content);
};
#endif  // SRC_VDFPARSER_VDFPARSER_HPP_
