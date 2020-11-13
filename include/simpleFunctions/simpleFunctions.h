#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "../gameItem/gameItem.h"
#include "../vdfParser/vdfParser.h"

using namespace std;

#ifndef SIMPLEFUNCTIONS_SIMPLEFUNCTIONS_H_
#define SIMPLEFUNCTIONS_SIMPLEFUNCTIONS_H_

#define T_L(x) TYTI_L(char, x)

// Adds \" to each side of the string
#define quote(x) #x

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

class SimpleFunctions {
 public:
    static bool workingVectorEqual(vector<string> ref, vector<string> comp) {
        if (ref.size() != comp.size()) return false;
        for (int index = 0; auto item : ref) {
            if (strcmp(item.c_str(), comp[index].c_str()) != 0) return false;
            index++;
        }
        return true;
    }

    static vector<string> stringSplitByString(string str, string token) {
        vector<string> result;
        if (str.size() <= 0) return result;
        while (str.size()) {
            int index = str.find(token);
            if (index != string::npos) {
                result.push_back(str.substr(0, index));
                str = str.substr(index + token.size());
                if (str.size() == 0) result.push_back(str);
            } else {
                result.push_back(str);
                str = "";
            }
        }
        return result;
    }

    static vector<string> stringSplitByChar(string split, char splitter) {
        vector<string> splitVector;
        string segment;
        std::istringstream streamString(split);
        while (std::getline(streamString, segment, splitter)) {
            splitVector.push_back(segment);
        }
        return splitVector;
    }
    static const string *charListToString(char const *list) {
        // https://stackoverflow.com/a/4643721/9376723
        string *str;
        str = new string;
        *str = list;
        return str;
    }

    static bool stringInList(string value, vector<string> list) {
        for (auto item : list) {
            if (value == item) {
                return true;
            }
        }
        return false;
    }

    static char *addChar(char const *first, char const *second) {
        size_t size = sizeof(char) + strlen(first) + strlen(second);
        char *str = reinterpret_cast<char *>(malloc(size));
        strcpy(str, first);
        strcat(str, second);
        return str;
    }

    static char *surroundChar(char const *first, char const *second, char const *third) {
        size_t size = sizeof(char) + strlen(first) + strlen(second) + strlen(third);
        char *str = reinterpret_cast<char *>(malloc(size));
        strcpy(str, first);
        strcat(str, second);
        strcat(str, third);
        return str;
    }

    static void timeFunction(void(func)()) {
        auto start = chrono::high_resolution_clock::now();
        func();
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout << duration.count() << endl;
    }

    static char *removeSpaces(char *s) {
        char *cpy = s;
        char *temp = s;
        while (*cpy) {
            if (*cpy != ' ') *temp++ = *cpy;
            cpy++;
        }
        *temp = 0;
        return s;
    }

    static vector<string> getDrives() {
        // string steamLib = string(getenv("HOME")) + "/.local/share/Steam/steamapps";
        // std::ifstream file(steamLib + "/libraryfolders.vdf");
        // auto root = tyti::vdf::read(file);
        // UserLocalConfigStore/Software/Valve/Steam/Apps/71/LaunchOptions
        // vector<string> pathList = {steamLib};
        // for (int i = 1; i < root.attribs.size(); i++) {
        //     string item = root.attribs[to_string(i)];
        //     if (item.size() > 0) {
        //         pathList.push_back(item + "/steamapps");
        //         continue;
        //     }
        //     break;
        // }
        // return pathList;
        vector<string> vec;
        return vec;
    }

    static GameItem::Game getGame(char *path) {
        // ifstream file(path);
        // auto root = tyti::vdf::read(file);
        // GameItem::Game game;
        // game.appID = root.attribs["appid"];
        // game.name = root.attribs["name"];
        // return game;
        GameItem::Game game;
        return game;
    }

    static string readGameOptions(string gameID) {
        return "";
        // ifstream file(string(getenv("HOME")) +
        //               "/.steam/steam/userdata/143352235/config/localconfig.vdf");
        // return tyti::vdf::read(file)
        //   .childs["Software"]
        //   ->childs["Valve"]
        //   ->childs["Steam"]
        //   ->childs["Apps"]
        //   ->childs[gameID]
        //   ->attribs["LaunchOptions"];
    }

    static string removeRCharFromString(const string &str, char ch) {
        string result = "";
        for (size_t i = 0; i < str.size(); i++) {
            if (str[i] != ch) {
                result += str[i];
            }
        }
        return result;
    }

    static string replaceCharInString(const string &str, char ch, char replace) {
        string result = "";
        for (size_t i = 0; i < str.size(); i++) {
            result += str[i] == ch ? replace : str[i];
        }
        return result;
    }

    static string removeCharRFromStart(string str, char ch) {
        while (true) {
            if (str.starts_with(ch)) {
                str = str.erase(0, 1);
                continue;
            }
            break;
        }
        return str;
    }

    template <typename S, typename T>
    static void findInMapFromPath(map<S, T> mappy, string path) {}
};
#endif  // SIMPLEFUNCTIONS_SIMPLEFUNCTIONS_H_
