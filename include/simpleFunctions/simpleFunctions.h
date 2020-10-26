#include <curl/curl.h>
#include <gtkmm-3.0/gtkmm.h>
#include <json-glib/json-glib.h>
#include <iostream>
#include <string>
#include <vector>
#include "../gameItem/gameItem.h"
#include "../vdfParser/vdfParser.h"

using namespace std;

#ifndef SIMPLEFUNCTIONS_SIMPLEFUNCTIONS_H_
#define SIMPLEFUNCTIONS_SIMPLEFUNCTIONS_H_

// Adds \" to each side of the string
#define quote(x) #x

class SimpleFunctions {
 public:
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

    static bool ifStrMatchList(string ref, vector<string> li) {
        for (auto it : li) {
            if (strstr(ref.c_str(), it.c_str())) {
                return true;
            }
        }
        return false;
    }

    static vector<string> getDrives() {
        string steamLib = string(getenv("HOME")) + "/.local/share/Steam/steamapps";
        std::ifstream file(steamLib + "/libraryfolders.vdf");
        auto root = tyti::vdf::read(file);
        vector<string> pathList = {steamLib};
        for (int i = 1; i < root.attribs.size(); i++) {
            string item = root.attribs[to_string(i)];
            if (item.size() > 0) {
                pathList.push_back(item + "/steamapps");
                continue;
            }
            break;
        }
        return pathList;
    }

    static GameItem::Game getGame(char *path) {
        ifstream file(path);
        auto root = tyti::vdf::read(file);
        GameItem::Game game;
        game.appID = root.attribs["appid"];
        game.name = root.attribs["name"];
        return game;
    }
};
#endif  // SIMPLEFUNCTIONS_SIMPLEFUNCTIONS_H_
