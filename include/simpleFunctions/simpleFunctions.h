#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include <map>
#include <memory>
#include <regex>
#include <string>
#include <vector>
#include "../gameItem/gameItem.h"
#include "../vdfParser/vdfParser.h"

using namespace std;

#ifndef INCLUDE_SIMPLEFUNCTIONS_SIMPLEFUNCTIONS_H_
#define INCLUDE_SIMPLEFUNCTIONS_SIMPLEFUNCTIONS_H_

#define T_L(x) TYTI_L(char, x)

// Adds quotes to each side of the string
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

template <typename S, typename T>
ostream &operator<<(ostream &out, const std::map<S, T> &v) {
    out << "{" << (v.size() > 0 ? "\n" : " ");
    size_t last = v.size() - 1;
    for (int index = 0; auto item : v) {
        out << "\t";
        out << item.first << ": " << item.second;
        if (index != last) out << ", ";
        out << "\n";
        index++;
    }
    out << "}\n";
    return out;
}

class SimpleFunctions {
 public:
    template <typename S>
    static bool vectorMatch(vector<S> ref, vector<S> comp, bool matchSize = true) {
        if (matchSize && ref.size() != comp.size()) return false;
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

    static bool stringInList(string ref, vector<string> li, bool lose = false) {
        for (string item : li) {
            if (lose) {
                if (strstr(ref.c_str(), item.c_str())) {
                    return true;
                }
            } else {
                if (ref == item) {
                    return true;
                }
            }
        }
        return false;
    }

    static string getSteamUserID() {
        string path = string(getenv("HOME")) + "/.local/share/Steam/config/loginusers.vdf";
        auto users = VdfParser(path).getFromPath("users");
        int steam32BitID = 0;
        for (auto user : users) {
            auto split = SimpleFunctions::stringSplitByChar(user.first, '/');
            if (split[1] == "MostRecent" && user.second == "1") {
                // Might cause error when converting a string to a 64Bit int when string
                // isn't numbers so checking with regex if only numbers
                if (regex_match(split[0], regex("^[0-9]*$"))) {
                    steam32BitID = stol(split[0]) - 76561197960265728;
                    break;
                }
            }
        }
        if (steam32BitID == 0) {
            cout << "Could not get 32bit Steam ID. Make sure that you're logged into Steam" << endl;
            exit(1);
        }
        return to_string(steam32BitID);
    }

    static vector<string> getDrives() {
        string steamLib = string(getenv("HOME")) + "/.local/share/Steam/steamapps";
        VdfParser parser = VdfParser(steamLib + "/libraryfolders.vdf");
        map<string, string> attributes = parser.getFromPath("LibraryFolders");
        vector<string> pathList = {steamLib};
        for (int i = 1; i < attributes.size(); i++) {
            string item = attributes[to_string(i)];
            if (item.size() > 0) {
                pathList.push_back(item + "/steamapps");
                continue;
            }
            break;
        }
        return pathList;
    }

    static GameItem::Game getGame(string path) {
        map<string, string> gameMap = VdfParser(path).getFromPath("AppState");
        GameItem::Game game;
        game.appID = gameMap["appid"];
        game.name = gameMap["name"];
        return game;
    }

    static string readGameOptions(string gameID, string userID) {
        string path = "/.steam/steam/userdata/" + userID + "/config/localconfig.vdf";
        return VdfParser(string(getenv("HOME")) + path)
          .getFromPath("UserLocalConfigStore/Software/Valve/Steam/Apps/" + gameID)["LaunchOptions"];
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
        for (char character : str) {
            result += character == ch ? replace : character;
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
};
#endif  // INCLUDE_SIMPLEFUNCTIONS_SIMPLEFUNCTIONS_H_
